#include "mainwindow.h"
#include "RepositoriesPage.h"
#include "../ui/ui_mainwindow.h"
#include "registerrepodialog.h"
#include <QSqlQueryModel>

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

    setActiveTab(ui->repositoriesNavButton);

    RepositoriesPage *repoWidget = new RepositoriesPage();

    // Show repo widget by default
    ui->mainContentStackedWidget->setCurrentIndex(0);

    // Connect the toggle button click to collapse/expand
    connect(ui->toggleButton, &QPushButton::clicked, this, &MainWindow::toggleNavbar);
    connect(ui->repositoriesNavButton, &QPushButton::clicked, this, [this]() { setActiveTab(ui->repositoriesNavButton); });
    connect(ui->branchNavButton, &QPushButton::clicked, this, [this]() { setActiveTab(ui->branchNavButton); });
    connect(ui->commitsNavButton, &QPushButton::clicked, this, [this]() { setActiveTab(ui->commitsNavButton); });
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

void MainWindow::setActiveTab(QPushButton *activeButton) {
    QList<QPushButton*> buttons = { ui->repositoriesNavButton, ui->branchNavButton, ui->commitsNavButton };
    for (auto btn : buttons) {
        btn->setChecked(btn == activeButton);
    }

    // Toggle stacked pages
    if (activeButton == ui->repositoriesNavButton) {
        ui->mainContentStackedWidget->setCurrentIndex(0);
        RepositoriesPage *repoWidget = qobject_cast<RepositoriesPage*>(
            ui->mainContentStackedWidget->currentWidget()
        );
        if (repoWidget) {
            repoWidget->loadRepositories();
        }
    } else if (activeButton == ui->repositoriesNavButton) {
        ui->mainContentStackedWidget->setCurrentIndex(1);
    } else if (activeButton == ui->repositoriesNavButton) {
        ui->mainContentStackedWidget->setCurrentIndex(2);
    }
}

