#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "database/databasemanager.h"
#include "models/notesmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    if (!DatabaseManager::instance().connect()) {
        qFatal("Could not connect to database!");
    }

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    NotesModel notesModel;

    engine.rootContext()->setContextProperty("notesModel", &notesModel);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("GigaNotes", "Main");

    return app.exec();
}
