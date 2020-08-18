#ifndef USERACTIVITY_FILE_H
#define USERACTIVITY_FILE_H

#include <QDialog>

namespace Ui {
class useractivity_file;
}

class useractivity_file : public QDialog
{
    Q_OBJECT

public:
    explicit useractivity_file(QWidget *parent = nullptr);
    ~useractivity_file();



private slots:

    void on_Add_user_clicked();

    void on_ConfirmUser_clicked();

    void on_AddActivity_clicked();

    void on_ConfirmActivity_clicked();

    void on_AddSubActivity_clicked();

    void on_ConfirmSubActivity_clicked();

private:
    Ui::useractivity_file *ui;
};

#endif // USERACTIVITY_FILE_H
