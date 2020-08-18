#ifndef USER_LIST_H
#define USER_LIST_H

#include <QDialog>
namespace Ui {
class user_list;
}

class user_list : public QDialog
{
    Q_OBJECT

public:
    explicit user_list(QWidget *parent = nullptr);
    ~user_list();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::user_list *ui;
};

#endif // USER_LIST_H
