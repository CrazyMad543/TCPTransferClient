#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "clientdata.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<ClientData>("Client.data", 1, 0, "ClientData");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
