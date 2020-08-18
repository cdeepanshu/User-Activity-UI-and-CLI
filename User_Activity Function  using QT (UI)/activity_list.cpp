#include "activity_list.h"
#include "ui_activity_list.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QFileDialog>

activity_list::activity_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activity_list)
{
    ui->setupUi(this);
}

activity_list::~activity_list()
{
    delete ui;
}

QString filename_activity;

void activity_list::on_pushButton_clicked()                                             //Push Button to Browse the file
{
    filename_activity=QFileDialog::getOpenFileName(this,"Browse File",QDir::homePath());
    ui->lineEdit->setText(filename_activity);
}

void activity_list::on_pushButton_2_clicked()                                  //Confirm button to open the file and show the file in table view
{
    QFile file(filename_activity);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"File",file.errorString());                //Message box will be displayed if there is error in opening of file
    }

    else{
     QStandardItemModel *model = new QStandardItemModel;                         //.csv file to table view

    QTextStream in(&file);
    int lineindex=0;

    while (!in.atEnd()) {                                                    //loop till the end of the file
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();                                            // Read file line by line

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

        file.close();                                                    //close the file

    ui->tableView->setModel(model);                                      //display the model as table view
    }
}
