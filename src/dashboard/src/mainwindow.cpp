#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "registerrepodialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FlowTrack");

     // Create controller — it will auto-run processQueuedEvents
    controller = new AppController(this);

    animation = new QPropertyAnimation(ui->navbarWidget, "maximumWidth");
    animation->setDuration(250);               // animation speed
    animation->setEasingCurve(QEasingCurve::InOutCubic);

    // Connect the toggle button click to collapse/expand
    connect(ui->toggleButton, &QPushButton::clicked, this, &MainWindow::toggleNavbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleNavbar()
{
    int currentWidth = ui->navbarWidget->width();
    int collapsedWidth = 50;
    int expandedWidth = 200;
    animation->stop();
    animation->setTargetObject(ui->navbarWidget);
    animation->setPropertyName("maximumWidth");
    animation->setDuration(250);
    animation->setEasingCurve(QEasingCurve::InOutCubic);

    if (!isCollapsed) {
        animation->setStartValue(currentWidth);
        animation->setEndValue(collapsedWidth);
        animation->start();
        isCollapsed = true;
        ui->toggleButton->setText("");
        ui->toggleButton->setIcon(QIcon(":/resources/icons/navbar-toggle-right.svg"));
    } else {
        animation->setStartValue(currentWidth);
        animation->setEndValue(expandedWidth);
        animation->start();
        isCollapsed = false;
        ui->toggleButton->setText("");
        ui->toggleButton->setIcon(QIcon(":/resources/icons/navbar-toggle-left.svg"));
    }
}

void MainWindow::on_connectButton_clicked()
{
    RegisterRepoDialog dialog(this);
    dialog.exec();
}

