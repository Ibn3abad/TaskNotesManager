/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "backend/DatabaseManager.h"
#include "backend/TaskModel.h"
#include "backend/NoteModel.h"
#include "backend/TodoModel.h"
#include "backend/Translator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("Ibn3abad");
    QGuiApplication::setApplicationName("TaskNest");

    QQuickStyle::setStyle("Fusion");

    DatabaseManager database;
    if (!database.openDatabase()) {
        qWarning() << "Database could not be opened.";
    }

    TaskModel taskModel(&database);
    NoteModel noteModel(&database);
    TodoModel todoModel(&database);
    Translator translator;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("taskModel", &taskModel);
    engine.rootContext()->setContextProperty("noteModel", &noteModel);
    engine.rootContext()->setContextProperty("todoModel", &todoModel);
    engine.rootContext()->setContextProperty("databaseManager", &database);
    engine.rootContext()->setContextProperty("i18n", &translator);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("TaskNotesManager", "Main");

    return app.exec();
}
