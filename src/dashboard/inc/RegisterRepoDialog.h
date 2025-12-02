#ifndef REGISTERREPODIALOG_H
#define REGISTERREPODIALOG_H

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
    void on_browseBtn_clicked();
    void on_submitBtn_clicked();

private:
    Ui::RegisterRepoDialog *ui;
};

#endif // REGISTERREPODIALOG_H
