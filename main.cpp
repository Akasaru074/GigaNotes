#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "database/databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    if (!DatabaseManager::instance().connect()) {
        qFatal("Could not connect to database!");
    }

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("GigaNotes", "Main");

    return app.exec();
}
