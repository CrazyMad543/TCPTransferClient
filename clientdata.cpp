#include "clientdata.h"

#include <QFileInfo>
#include <QDebug>
#include <QUrl>

ClientData::ClientData(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    m_sizeFile = "0";
    m_filePath = "";
    m_value = 0.0;
}

void ClientData::sendFile(const QString &host, const QString &port) {
    socket->connectToHost(host, port.toInt(), QIODevice::WriteOnly);
    socket->waitForConnected();
}

void ClientData::openFile(const QString& urlFile) {
    transferFile = new QFile(QUrl(urlFile).toLocalFile());
    if(transferFile->open(QIODevice::ReadOnly)) {
        m_sizeFile = QString::number(QFileInfo(QUrl(urlFile).toLocalFile()).size()) + " Bytes";
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
