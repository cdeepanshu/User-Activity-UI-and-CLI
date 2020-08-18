#ifndef ACTIVITY_LIST_H
#define ACTIVITY_LIST_H

#include <QDialog>
namespace Ui {
class activity_list;
}

class activity_list : public QDialog
{
    Q_OBJECT

public:
    explicit activity_list(QWidget *parent = nullptr);
    ~activity_list();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::activity_list *ui;
};

#endif // ACTIVITY_LIST_H
