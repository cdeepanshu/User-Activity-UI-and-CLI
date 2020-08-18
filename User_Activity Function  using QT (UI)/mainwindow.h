#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user_list.h"
#include "activity_list.h"
#include "subactivity_list.h"
#include "useractivity_file.h"
#include "comparison_file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    user_list *u_list;
    activity_list *a_list;
    subactivity_list *s_list;
    useractivity_file *ua_file;
    comparison_file *comp_file;


};
#endif // MAINWINDOW_H
