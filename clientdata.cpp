#include "clientdata.h"

#include <QFileInfo>
#include <QUrl>

ClientData::ClientData(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    m_sizeFile = "0";
    m_filePath = "";
    m_value = 0.0;
    transferSize = 0;
}

ClientData::~ClientData() {
    delete socket;
}

void ClientData::sendFile(const QString &host, const QString &port) {
    socket->connectToHost(host, port.toInt(), QIODevice::WriteOnly);
    if(!socket->waitForConnected())
        return;

    connect(socket, &QTcpSocket::bytesWritten, this, &ClientData::sendPartFile);
    sendPartFile();
}

void ClientData::sendPartFile() {
    char data[1024];
    if(!transferFile->atEnd()) {
        quint64 receivedSize = transferFile->read(data, sizeof(data));
        socket->write(data, receivedSize);

        transferSize += receivedSize;
        m_value = (double)transferSize / (double)transferFile->size();
        emit valueChanged();
    } else {
        transferFile->close();
        transferFile = NULL;

        socket->disconnectFromHost();

        disconnect(socket, &QTcpSocket::bytesWritten, this, &ClientData::sendPartFile);

        m_sizeFile = "0";
        emit sizeFileChanged();
        m_filePath = "";
        emit filePathChanged();
        m_value = 0.0;
        emit valueChanged();
    }
}

void ClientData::openFile(const QString& urlFile) {
    transferFile = new QFile(QUrl(urlFile).toLocalFile());
    if(transferFile->open(QIODevice::ReadOnly)) {
        m_sizeFile = QString::number(transferFile->size()) + " Bytes";
        emit sizeFileChanged();
        m_filePath = QUrl(urlFile).toLocalFile();
        emit filePathChanged();
        m_value = 0.0;
        emit valueChanged();
    } else {
        m_sizeFile = "0";
        emit sizeFileChanged();
        m_filePath = "Error file";
        emit filePathChanged();
        m_value = 0.0;
        emit valueChanged();
    }
}
