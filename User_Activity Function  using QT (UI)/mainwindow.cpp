#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()                         //Push Button for user file
{
    u_list = new user_list(this);
    u_list->show();
}

void MainWindow::on_pushButton_2_clicked()                          //Push Button for Activities File
{
    a_list = new activity_list(this);
    a_list->show();
}

void MainWindow::on_pushButton_3_clicked()                           //Push Button for Sub Activities File
{
    s_list = new subactivity_list(this);
    s_list->show();
}

void MainWindow::on_pushButton_4_clicked()                             // Push Button for user-ativity-subactivity funtion
{
    ua_file = new useractivity_file(this);
    ua_file->show();
}

void MainWindow::on_pushButton_5_clicked()                             //Push Button for comparison
{
    comp_file = new comparison_file(this);
    comp_file->show();
}
