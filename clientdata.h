#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QObject>

class QFile;

class ClientData : public QObject {
    Q_OBJECT
public:
    explicit ClientData(QObject *parent = 0);

    Q_PROPERTY(QString sizeFile READ getSizeFile NOTIFY sizeFileChanged)
    Q_PROPERTY(QString filePath READ getFilePath NOTIFY filePathChanged)

    Q_INVOKABLE void openFile(const QString& urlFile);

public:
    QString getSizeFile() const { return m_sizeFile; }
    QString getFilePath() const { return m_filePath; }

signals:
    void sizeFileChanged();
    void filePathChanged();

public slots:

private:
    QFile *transferFile;
    QString m_sizeFile;
    QString m_filePath;
    int unit;
    QStringList units = {" Bytes", " kB", " MB", " GB"};

};

#endif // CLIENTDATA_H
