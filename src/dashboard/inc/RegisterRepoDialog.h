#ifndef REGISTERREPO_DIALOG_H
#define REGISTERREPO_DIALOG_H

#include <QDialog>

namespace Ui {
class RegisterRepoDialog;
}

class RegisterRepoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterRepoDialog(QWidget *parent = nullptr);
    ~RegisterRepoDialog();

private slots:
    void on_buttonBox_accepted();
    void on_browseButton_clicked();

private:
    Ui::RegisterRepoDialog *ui;
};

#endif // REGISTERREPODIALOG_H
