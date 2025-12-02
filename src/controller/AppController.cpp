#include "AppController.h"
#include "../app/App.h"

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    App::instance()->processor()->processQueuedEvents();
    qDebug() << "AppController: Queued events processed at startup";

    // Emit signal if UI wants to know
    emit processed();
}
