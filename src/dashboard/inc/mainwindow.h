#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleNavbar();
    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isCollapsed = false;
    AppController* controller;
    QPropertyAnimation *animation;

};
#endif // MAINWINDOW_H
