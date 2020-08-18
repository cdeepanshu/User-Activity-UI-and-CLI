#ifndef SUBACTIVITY_LIST_H
#define SUBACTIVITY_LIST_H

#include <QDialog>
namespace Ui {
class subactivity_list;
}

class subactivity_list : public QDialog
{
    Q_OBJECT

public:
    explicit subactivity_list(QWidget *parent = nullptr);
    ~subactivity_list();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::subactivity_list *ui;
};

#endif // SUBACTIVITY_LIST_H
