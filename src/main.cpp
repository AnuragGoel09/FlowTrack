#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app/App.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    App::instance()->start(); // starts DB, processor and server

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    // Fallback: debug if empty
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML";
        return -1;
}
    if (engine.rootObjects().isEmpty())
        return -1;

    int ret = app.exec();

    App::instance()->stop();
    return ret;
}
