#include <QApplication>
#include <QFile>
#include "app/App.h"
#include "dashboard/inc/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if(!Database::initDefault()){
        qDebug() << "Error in initializing DB";
        return 0;
    }
    QFile styleFile(":/resources/style.qss");
    styleFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleFile.readAll());
    App::instance()->start(); // backend still starts same
    
    MainWindow w;
    w.show();

    int ret = app.exec();

    App::instance()->stop();
    return ret;
}
