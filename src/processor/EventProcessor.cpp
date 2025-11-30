#include "EventProcessor.h"
#include "../db/Database.h"
#include "../models/GitEvent.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

EventProcessor::EventProcessor(Database *db, QObject *parent): QObject(parent), _db(db) {}

QString EventProcessor::queuePath() const {
    return QDir::homePath() + "/.flowTrack-events";
}

void EventProcessor::processEventJson(const QString &jsonText) {
    auto doc = QJsonDocument::fromJson(jsonText.toUtf8());
    if (!doc.isObject()) {
        qDebug() << "Invalid event JSON";
        return;
    }
    GitEvent e = GitEvent::fromJson(doc.object());
    // basic handling: insert commit if not exists
    if (e.type == "commit" || e.type == "cherry-pick") {
        _db->insertCommit(e.hash, e.branch, e.message, e.author, e.timestamp);
        qDebug() << "Processed commit" << e.hash << "branch" << e.branch;
    } else {
        qDebug() << "Unhandled event type" << e.type;
    }
}

void EventProcessor::processQueuedEvents() {
    QDir dir(queuePath());
    if (!dir.exists()) {
        QDir().mkpath(dir.path());
        return;
    }
    auto entries = dir.entryList(QStringList() << "*.json", QDir::Files, QDir::Name);
    for (const QString &fname : entries) {
        QString full = dir.filePath(fname);
        QFile f(full);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) continue;
        QString txt = f.readAll();
        f.close();
        processEventJson(txt);
        // delete after processed
        QFile::remove(full);
    }
}

void EventProcessor::stop() {
    // nothing special now
}
