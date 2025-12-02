#include "RegisterRepoDialog.h"
#include "ui_RegisterRepoDialog.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>

RegisterRepoDialog::RegisterRepoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterRepoDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    setWindowTitle("Connect Git Repository");
}

RegisterRepoDialog::~RegisterRepoDialog()
{
    delete ui;
}

void RegisterRepoDialog::on_browseButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Repository Directory");
    if (!dir.isEmpty()) {
        ui->pathEdit->setText(dir);
    }
}


void RegisterRepoDialog::on_buttonBox_accepted()
{
    QString repoPath = ui->pathEdit->text().trimmed();
    QString repoName = ui->repoNameEdit->text().trimmed();

   if (repoName.isEmpty() || repoName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please provide the name of the repository for reference");
        return;
    }

    if (repoPath.isEmpty() || repoName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please provide the folder path of repository");
        return;
    }

    if (!QDir(repoPath + "/.git").exists()) {
        QMessageBox::warning(this, "Warning", "Not a valid Git repository");
        return;
    }

    QMessageBox::information(this, "Success", "Valid Git repository");
    accept();
}
