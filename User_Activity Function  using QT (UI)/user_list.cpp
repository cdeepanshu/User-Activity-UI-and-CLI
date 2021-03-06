#include "user_list.h"
#include "ui_user_list.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QFileDialog>

user_list::user_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_list)
{
    ui->setupUi(this);
}

user_list::~user_list()
{
    delete ui;
}

QString filename_user;


void user_list::on_pushButton_clicked()                                //Push Button to Browse the file
{
   filename_user=QFileDialog::getOpenFileName(this,"Browse File",QDir::homePath());
   ui->lineEdit->setText(filename_user);

}

void user_list::on_pushButton_2_clicked()                              //Confirm button to open the file and show the file in table view
{
    QFile file(filename_user);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"File",file.errorString());          //Message box will be displayed if there is error in opening of file
    }
    else{                                                              //.csv file to table view
     QStandardItemModel *model = new QStandardItemModel;

    QTextStream in(&file);
    int lineindex=0;

    while (!in.atEnd()) {                                               //loop till the end of the file
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();                             // Read file line by line

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);

            // load parsed data to model accordingly
            for (int j = 0; j < lineToken.size(); j++) {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
                //ui->tableView->setModel(model);

            }
            lineindex++;
        }

        file.close();                                                                   //close the file

    ui->tableView->setModel(model);                                                    //display the model as table view
    }
}
