#pragma once
#include <QString>
#include <QJsonObject>

struct GitEvent {
    QString type;    // "commit", "cherry-pick", "push", etc.
    QString hash;
    QString branch;
    QString message;
    QString author;
    QString timestamp;

    static GitEvent fromJson(const QJsonObject& o) {
        return {
            o.value("type").toString(),
            o.value("hash").toString(),
            o.value("branch").toString(),
            o.value("message").toString(),
            o.value("author").toString(),
            o.value("timestamp").toString()
        };
    }

    QJsonObject toJson() const {
        QJsonObject o;
        o["type"] = type;
        o["hash"] = hash;
        o["branch"] = branch;
        o["message"] = message;
        o["author"] = author;
        o["timestamp"] = timestamp;
        return o;
    }
};
