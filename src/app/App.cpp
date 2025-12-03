#include "App.h"
#include "../db/Database.h"
#include "../server/EventServer.h"
#include "../processor/EventProcessor.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

App* App::_inst = nullptr;

App* App::instance() {
    if (!_inst) _inst = new App(nullptr);
    return _inst;
}

App::App(QObject* parent): QObject(parent) {}

void App::start() {
    // Ensure data dir exists
    QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appData);

    _db = std::make_unique<Database>(appData + "/flowTrack.db");
    _db->migrateIfNeeded();

    _processor = std::make_unique<EventProcessor>(_db.get());
    _processor->processQueuedEvents(); // process queue at startup

    _server = std::make_unique<EventServer>(_db.get(), _processor.get());
    _server->start(8989);

    qDebug() << "App started";
}

void App::stop() {
    if (_server) _server->stop();
    if (_processor) _processor->stop();
    qDebug() << "App stopped";
}

Database* App::database() const { return _db.get(); }
EventServer* App::server() const { return _server.get(); }
EventProcessor* App::processor() const { return _processor.get(); }
