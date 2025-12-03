#include "RepositoriesPage.h"
#include "ui_RepositoriesPage.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

RepositoriesPage::RepositoriesPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RepositoriesPage)
{
    ui->setupUi(this);
    
}

RepositoriesPage::~RepositoriesPage()
{
    delete ui;
}


void RepositoriesPage::loadRepositories() {
    auto *model = new QSqlQueryModel(this);

    model->setQuery("SELECT name, path, last_commit_hash, last_commit_time FROM repositories");
    qDebug() << "Loading repositories";
    ui->tableWidget->setRowCount(0); // clear existing rows
    // model->setHeaderData(0, Qt::Horizontal, "Name");
    // model->setHeaderData(1, Qt::Horizontal, "Path");
    // model->setHeaderData(2, Qt::Horizontal, "Last Commit");
    // model->setHeaderData(3, Qt::Horizontal, "Last Commit Time");

    // ui->tableWidget->setModel(model);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

}