#include "clientdata.h"

#include <QFileInfo>
#include <QDebug>
#include <QUrl>

ClientData::ClientData(QObject *parent) : QObject(parent), m_sizeFile("0"), m_filePath("") {

}

void ClientData::openFile(const QString& urlFile) {
    transferFile = new QFile(QUrl(urlFile).toLocalFile());
    if(transferFile->open(QIODevice::ReadOnly)) {
        m_sizeFile = QString::number(QFileInfo(QUrl(urlFile).toLocalFile()).size() / (1024 * 1024), 'f', 3) + " MB";
        emit sizeFileChanged();
        m_filePath = QUrl(urlFile).toLocalFile();
        emit filePathChanged();
    } else {
        m_sizeFile = "0";
        emit sizeFileChanged();
        m_filePath = "Error file";
        emit filePathChanged();
    }
}
