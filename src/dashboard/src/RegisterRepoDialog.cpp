#include "RegisterRepoDialog.h"
#include "ui_RegisterRepoDialog.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>

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

    QString hooksPath = repoPath + "/.git/hooks";

    // Hook script content
    QString hookScript =
R"(#!/bin/sh
# FlowTrack Hooks Script

SCRIPT_NAME=$(basename "$0")

case "$SCRIPT_NAME" in
    post-commit) EVENT_TYPE="commit" ;;
    post-merge) EVENT_TYPE="merge" ;;
    post-cherry-pick) EVENT_TYPE="cherry-pick" ;;
    post-rewrite) EVENT_TYPE="rewrite" ;;
    *) EVENT_TYPE="unknown" ;;
esac
HASH=$(git rev-parse HEAD)
BRANCH=$(git rev-parse --abbrev-ref HEAD)
MESSAGE=$(git log -1 --pretty=%B)

JSON="{\"type\":\"${EVENT_TYPE}\", \"hash\":\"${HASH}\", \"branch\":\"${BRANCH}\", \"message\":\"${MESSAGE}\"}"

APPDATA="$HOME/.flowTrack-events"

mkdir -p "$APPDATA"

QUEUEFILE="$APPDATA/event-$(date +%s).json"
echo $JSON > "$QUEUEFILE"

curl -X POST http://localhost:8989/event -H "Content-Type: application/json" -d "$JSON" || exit 0

)";

    // Write each hook file
    QStringList hookFiles = { "post-commit", "post-merge", "post-rewrite", "post-cherry-pick" };

    for (const QString &name : hookFiles) {
        QFile file(hooksPath + "/" + name);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            file.write(hookScript.toUtf8());
            file.close();
#ifdef Q_OS_LINUX
            QFile::setPermissions(file.fileName(), QFileDevice::ExeUser | QFileDevice::ReadUser);
#endif
        } else {
            QMessageBox::critical(this, "Error",
                "Failed to create hook: " + name + "\nCheck file permissions.");
            return;
        }
    }

    // Insert repo entry into DB (example)
    QSqlQuery query;
    query.prepare("INSERT INTO repositories(repoName, repoPath) VALUES(:name,:path)");
    query.bindValue(":name", repoName);
    query.bindValue(":path", repoPath);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Repository integrated successfully!");
    accept();
}
