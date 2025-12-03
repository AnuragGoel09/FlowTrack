#ifndef REPOSITORIES_PAGE_H
#define REPOSITORIES_PAGE_H

#include <QDialog>

namespace Ui {
class RepositoriesPage;
}

class RepositoriesPage : public QWidget
{
    Q_OBJECT

public:
    explicit RepositoriesPage(QWidget *parent = nullptr);
    ~RepositoriesPage();

    void loadRepositories();

// private slots:
//     void on_buttonBox_accepted();
//     void on_browseButton_clicked();

private:
    Ui::RepositoriesPage *ui;

};

#endif // REPOSITORIES_PAGE_H
