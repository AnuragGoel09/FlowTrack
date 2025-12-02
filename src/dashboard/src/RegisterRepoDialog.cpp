#include "registerrepodialog.h"
#include "../ui/ui_RegisterRepoDialog.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>

RegisterRepoDialog::RegisterRepoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterRepoDialog)
{
    ui->setupUi(this);
}

RegisterRepoDialog::~RegisterRepoDialog()
{
    delete ui;
}

void RegisterRepoDialog::on_browseBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Repository Directory");
    if (!dir.isEmpty()) {
        ui->pathEdit->setText(dir);
    }
}

void RegisterRepoDialog::on_submitBtn_clicked()
{
    QString repoPath = ui->pathEdit->text();
    QString repoName = ui->repoNameEdit->text();

    if (repoPath.isEmpty() || repoName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields");
        return;
    }

    if (!QDir(repoPath + "/.git").exists()) {
        QMessageBox::warning(this, "Error", "Not a valid Git repository");
        return;
    }

    QMessageBox::information(this, "Success", "Valid Git repository");
    accept();
}
