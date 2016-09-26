#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QObject>
#include <QTcpSocket>

class QFile;

class ClientData : public QObject {
    Q_OBJECT
public:
    explicit ClientData(QObject *parent = 0);

    Q_PROPERTY(float value READ getValue NOTIFY valueChanged)
    Q_PROPERTY(QString sizeFile READ getSizeFile NOTIFY sizeFileChanged)
    Q_PROPERTY(QString filePath READ getFilePath NOTIFY filePathChanged)

    Q_INVOKABLE void openFile(const QString& urlFile);
    Q_INVOKABLE void sendFile(const QString& host, const QString& port);

public:
    qint64 getValue() const { return m_value; }
    QString getSizeFile() const { return m_sizeFile; }
    QString getFilePath() const { return m_filePath; }

signals:
    void valueChanged();
    void sizeFileChanged();
    void filePathChanged();

public slots:

private:
    QTcpSocket *socket;
    QFile *transferFile;
    float m_value;
    QString m_sizeFile;
    QString m_filePath;

};

#endif // CLIENTDATA_H
