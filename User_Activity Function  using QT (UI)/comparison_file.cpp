#include "comparison_file.h"
#include "ui_comparison_file.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QFileDialog>
#include <sstream>
#include <string>

comparison_file::comparison_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comparison_file)
{
    ui->setupUi(this);
}

comparison_file::~comparison_file()
{
    delete ui;
}


void comparison_file::on_comparison_clicked()                                   //Push Button to compare users
{
    QString user1=ui->lineEdit->text();                                        //User_id of first user
    QString user2=ui->lineEdit_2->text();                                      //User_id of Second user
    long long int average=0,no_of_files=0;
    QString u1filename,u2filename,u1file,u2file;

    QFile comparisonfile("C:/Users/hp/Documents/QT1/comparison.csv");               //Comparison file path

    if(!comparisonfile.open(QFile::WriteOnly)){
        QMessageBox::information(this,"File",comparisonfile.errorString());           //Dialouge Box if there is error in opening of file
    }
    QTextStream c_file(&comparisonfile);
    c_file<<"User1"<<","<<"User2"<<","<<"Average Comparison"<<endl;                     //output in the csv file

    for(int i=0;i<10;i++)                                                             //loop for user_1 files
    {
        QVector<QString>u1vector;                                                     //Vector to store user_1 file content line by line
        QString s=QString::number(i);
        u1file=user1+"_"+s;
        u1filename="C:/Users/hp/Documents/QT1/" + user1 +"_"+s+".csv";               //first user file path
        QFile u1_file(u1filename);
        if(u1_file.exists())                                                        //condition to check whether file exist or not
        {
            no_of_files++;
            if(!u1_file.open(QIODevice::ReadOnly)){
                QMessageBox::information(this,"File",u1_file.errorString());        //Dialouge Box if there is error in opening of file
            }

            QTextStream in(&u1_file);
               while (!in.atEnd())
               {
                  u1vector.push_back(in.readLine());
               }

            for(int j=0;j<10;j++)                                                  //loop for user_2 files
            {
                long long int u2_avg=0;
                QVector<QString>u2vector;                                          //vector to store user_2 file content line by line
                QString s1=QString::number(j);
                u2file=user2+"_"+s1;
                u2filename="C:/Users/hp/Documents/QT1/" + user2 +"_"+s1+".csv";        //second user file path
                QFile u2_file(u2filename);
                if(u2_file.exists())
                {
                    if(!u2_file.open(QIODevice::ReadOnly)){
                        QMessageBox::information(this,"File",u2_file.errorString());      //Dialouge Box if there is error in opening of file
                    }
                    QTextStream in1(&u2_file);
                       while (!in1.atEnd())
                       {
                          u2vector.push_back(in1.readLine());
                       }
                       for(int x=1;x<u1vector.size();x++)                            //loop for user1 check each line
                       {
                           int max=INT_MIN;
                           QString u1data=u1vector[x];                               //store file line by line
                           std::string s=u1data.toStdString();
                           std::string w1;
                           std::stringstream iss1;
                           iss1.str(s);
                           for(int y=1;y<u2vector.size();y++)                     //loop for user2
                           {
                               long long int match=0,not_match=0,count=-1;
                               QString u2data=u2vector[y];
                               std::string s1=u2data.toStdString();
                               std::string w2;
                               std::stringstream iss2;
                               iss2.str(s1);
                               while(iss1>>w1)                       //user1 line  content word by word
                               {
                                   if(w1!=","&&w1!="-")             //if line contain , or - don't proceed
                                   {
                                       while(iss2>>w2)                //user2 line  content word by word
                                       {
                                           if(w2!=","&&w2!="-")        //if line contain , or - don't proceed
                                           {
                                               if(w1==w2)               //if user1 word matches with user2 increment match
                                               {
                                                   match++;
                                               }
                                               else
                                               {
                                                   not_match++;                //if user1 word matches with user2 increment match
                                               }
                                           }
                                       }
                                   }
                               }
                               if(user1!=user2)                       //if we consider different users the decrement not match by one for u_id
                               {
                                   if(not_match>0)
                                   {
                                       not_match++;
                                   }
                               }
                               if(match>=not_match)                            //if match greater or equal to not match give 100 points
                               {
                                   count=100;
                               }
                               else if(match==not_match-1)                     //if match one less to not match give 50 points
                               {
                                   count=50;
                               }
                               else if(match==not_match-2)                     //if match is two less to not match give 25 points
                               {
                                   count=25;
                               }
                               else
                               {
                                   count=0;
                               }

                               if(count>max)                                   //maximum value of count
                               {
                                   max=count;
                               }
                           }
                           u2_avg=u2_avg+max;                                  //sum of each maximum value foe each file
                       }
                       u2_file.close();                                       //close user2 file
                       u2_avg=u2_avg/u1vector.size();                           //per file average
                       average=average+u2_avg;
                       c_file<<u1file<<","<<u2file<<","<<u2_avg<<endl;            //output at the comparison file
                }
            }
        }
        u1_file.close();                                                     //close user1 file
    }
    if(average!=0||no_of_files!=0)
    {
        average=average/no_of_files;                                           //overall comparison
    }
    c_file<<"Overall comparison between users"<<","<<average<<endl;                 //overall comparison in the csv file
    QString avg=QString::number(average);
    ui->lineEdit_3->setText(avg);                                                  //overall comparison the output window
    comparisonfile.close();                                                    //close the coparison file

}
