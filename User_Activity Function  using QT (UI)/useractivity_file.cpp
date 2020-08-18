#include "useractivity_file.h"
#include "ui_useractivity_file.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QRegularExpression>
#include <sstream>
#include <QSet>

useractivity_file::useractivity_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::useractivity_file)
{
    ui->setupUi(this);
}

useractivity_file::~useractivity_file()
{
    delete ui;
}


QString userid_file;
QString userid;
QString activityid;
QString subactivityid;

int activity=0,subactivity=0,line=0;

void useractivity_file::on_Add_user_clicked()                               //Push Button to add user
{
    activity=0;
    subactivity=0;
    line=0;
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();                                                //clear all the lines
    ui->lineEdit_3->clear();
    QFile userfile(userid_file);
    if(!userfile.open(QFile::ReadOnly)){
        QMessageBox::information(this,"File",userfile.errorString());               //Dialouge box if file can not open
    }
    //QTextStream r_file(&userfile);
    userfile.close();                                                             //close the file
}

void useractivity_file::on_ConfirmUser_clicked()                               //Push Button to confirm the User_Id
{
    userid = ui->lineEdit->text();                                              //Input the user id
    for(int i=0;i<INT_MAX;i++)
    {
        QString s=QString::number(i);
        userid_file="C:/Users/hp/Documents/QT1/" + userid +"_"+s+".csv";               //User if file path
        QFile ufile(userid_file);
        if(!ufile.exists())                                                          //if file not exist then create the file and break the loop
        {
            break;
        }

    }

    QFile userfile(userid_file);
    if(!userfile.open(QFile::WriteOnly|QFile::Append)){
        QMessageBox::information(this,"File",userfile.errorString());                 //Dialouge Box if there is error in opening of file
    }
    QTextStream r_file(&userfile);
    r_file<<"U_ID"<<","<<"A_ID"<<","<<"Sub_A_ID"<<endl;                              //Heading in the user file
    userfile.close();                                                              //Close the file

}

void useractivity_file::on_AddActivity_clicked()                                  //Push Button to add activity
{
    QSet<QString> set;
    line++;
    activity++;
    ui->lineEdit_2->clear();                                                       //clear the previous activity_id

    //For line break
    if(line!=1)
    {
    QFile userfile(userid_file);
    if(!userfile.open(QFile::WriteOnly|QFile::Append)){
        QMessageBox::information(this,"File",userfile.errorString());              //Dialouge Box if there is error in opening of file
    }
    QTextStream r_file(&userfile);
    r_file<<endl;                                                                //new line foe new activity
    userfile.close();                                                          //close the file
    }

    //Suggestion part begins

    if(activity==1)
    {
        QVector<QString>new_data;

        for(int i=1;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                QVector<QString>s_data;
                QString id=QString::number(i);
                QString id1=QString::number(j);
                QString uid;
                uid="C:/Users/hp/Documents/QT1/" + id +"_"+id1+".csv";
                QFile ufile(uid);
                if(ufile.exists()&&uid!=userid_file)
                {
                    QFile uidfile(uid);
                    if(!uidfile.open(QIODevice::ReadOnly)){
                        QMessageBox::information(this,"File",uidfile.errorString());        //Dialouge Box if there is error in opening of file
                    }
                    QTextStream u_file(&uidfile);
                    while(!u_file.atEnd())
                    {
                        s_data.push_back(u_file.readLine());
                    }

                    if(s_data.size()-1>=activity)
                    {

                            int comma=0;

                            QString udata=s_data[activity];                               //store file line by line
                            std::string s=udata.toStdString();
                            std::string w1;
                            std::stringstream iss1;
                            iss1.str(s);
                            while(iss1>>w1)                       //user1 line  content word by word
                            {

                                if(comma==1&&w1!=",")
                                {
                                    QString d=QString::fromStdString(w1);
                                    if(!set.contains(d))
                                    {
                                    new_data.push_back(d);
                                    set.insert(d);
                                    }

                                    //break;
                                }
                                if(w1==",")             //if line contain , or - don't proceed
                                {
                                    comma++;
                                }
                            }

                        }
                        uidfile.close();
                }
            }
        }


        QFile activitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_activities.txt");
        if(!activitysuggestionfile.open(QIODevice::WriteOnly|QIODevice::Text)){
            QMessageBox::information(this,"File",activitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
        }
        QTextStream s_file(&activitysuggestionfile);
        for(int i=0;i<new_data.size();i++)
        {
            s_file<<new_data[i]<<endl;
        }
        activitysuggestionfile.close();                                                          //close the file

    }


        //Printing of suggestion file data

        QFile activitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_activities.txt");
        if(!activitysuggestionfile.open(QIODevice::ReadOnly|QIODevice::Text)){
            QMessageBox::information(this,"File",activitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
        }
        QTextStream s_file(&activitysuggestionfile);

        ui->textBrowser->setText(s_file.readAll());
        activitysuggestionfile.close();                                                          //close the file

}


void useractivity_file::on_ConfirmActivity_clicked()                               //Push Button to confirm the Activity_id
{
    activityid = ui->lineEdit_2->text();                                         //Input the activity_id

    QFile userfile(userid_file);
    if(!userfile.open(QFile::WriteOnly|QFile::Append)){
        QMessageBox::information(this,"File",userfile.errorString());               //Dialouge Box if there is error in opening of file
    }
    QTextStream r_file(&userfile);
    r_file<<userid<<" , "<<activityid<<" , ";                                      //Output the user_id and activity_id in the file
    userfile.close();                                                             //close the file

    //suggestion part begins

    QSet<QString>set;
    QVector<QString>new_data;

    for(int i=1;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            QVector<QString>s_data;
            QString id=QString::number(i);
            QString id1=QString::number(j);
            QString uid;
            uid="C:/Users/hp/Documents/QT1/" + id +"_"+id1+".csv";
            QFile ufile(uid);
            if(ufile.exists()&&uid!=userid_file)
            {
                QFile uidfile(uid);
                if(!uidfile.open(QIODevice::ReadOnly)){
                    QMessageBox::information(this,"File",uidfile.errorString());        //Dialouge Box if there is error in opening of file
                }
                QTextStream u_file(&uidfile);
                while(!u_file.atEnd())
                {
                    s_data.push_back(u_file.readLine());
                }

                if(s_data.size()-1>=activity+1)
                {

                        int comma=0;

                        QString udata=s_data[activity];                               //store file line by line
                        std::string s=udata.toStdString();
                        std::string w1;
                        std::stringstream iss1;
                        iss1.str(s);
                        while(iss1>>w1)                       //user1 line  content word by word
                        {

                            if(comma==1&&w1!=",")
                            {
                                QString d=QString::fromStdString(w1);
                                if(d==activityid)
                                {
                                    int comma1=0;
                                    QString udata1=s_data[activity+1];                               //store file line by line
                                    std::string s1=udata1.toStdString();
                                    std::string w2;
                                    std::stringstream iss2;
                                    iss2.str(s1);
                                    while(iss2>>w2)
                                    {
                                        if(comma1==1&&w2!=",")
                                        {
                                            QString d1=QString::fromStdString(w2);
                                            if(!set.contains(d1))
                                            {
                                            new_data.push_back(d1);
                                            set.insert(d1);
                                            }
                                            break;


                                        }
                                        if(w2==",")
                                        {
                                            comma1++;
                                        }
                                    }
                                }

                            }
                            if(w1==",")             //if line contain , or - don't proceed
                            {
                                comma++;
                            }
                        }

                    }
                    uidfile.close();
            }
        }
    }

    //Storing data to suggestion file part

    QFile activitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_activities.txt");
    if(!activitysuggestionfile.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::information(this,"File",activitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
    }
    QTextStream s_file(&activitysuggestionfile);
    for(int i=0;i<new_data.size();i++)
    {
        s_file<<new_data[i]<<endl;
    }
    activitysuggestionfile.close();                                                          //close the file

}

void useractivity_file::on_AddSubActivity_clicked()                           //Push button to add sub-activity
{
    ui->lineEdit_3->clear();                                                  //clear the previous sub activity

    //suggestion part begins
    QSet<QString>set;
    subactivity++;

    if(subactivity==1)
    {
        QVector<QString>new_data;

        for(int i=1;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                QVector<QString>s_data;
                QString id=QString::number(i);
                QString id1=QString::number(j);
                QString uid;
                uid="C:/Users/hp/Documents/QT1/" + id +"_"+id1+".csv";
                QFile ufile(uid);
                if(ufile.exists()&&uid!=userid_file)
                {
                    QFile uidfile(uid);
                    if(!uidfile.open(QIODevice::ReadOnly)){
                        QMessageBox::information(this,"File",uidfile.errorString());        //Dialouge Box if there is error in opening of file
                    }
                    QTextStream u_file(&uidfile);
                    while(!u_file.atEnd())
                    {
                        s_data.push_back(u_file.readLine());
                    }

                    for(int x=1;x<s_data.size();x++)
                    {

                            int comma=0,sub=0;

                            QString udata=s_data[x];                               //store file line by line
                            std::string s=udata.toStdString();
                            std::string w1;
                            std::stringstream iss1;
                            iss1.str(s);
                            while(iss1>>w1)                       //user1 line  content word by word
                            {

                                if(comma==2&&w1!="-")
                                {
                                    sub++;
                                    if(sub==subactivity)
                                    {

                                    QString d=QString::fromStdString(w1);
                                        if(!set.contains(d))
                                        {
                                        new_data.push_back(d);
                                        set.insert(d);
                                        }
                                    break;
                                    }

                                }
                                if(w1==",")             //if line contain , or - don't proceed
                                {
                                    comma++;
                                }
                            }

                        }
                        uidfile.close();
                }
            }
        }

        //storing data to file part begins

        QFile subactivitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_sub-activities.txt");
        if(!subactivitysuggestionfile.open(QIODevice::WriteOnly|QIODevice::Text)){
            QMessageBox::information(this,"File",subactivitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
        }
        QTextStream s_file(&subactivitysuggestionfile);
        for(int i=0;i<new_data.size();i++)
        {
            s_file<<new_data[i]<<endl;
        }
        subactivitysuggestionfile.close();                                                          //close the file

    }                    //end of if case


   //Printing of sub-activity suggestion file

    QFile subactivitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_sub-activities.txt");
    if(!subactivitysuggestionfile.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"File",subactivitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
    }
    QTextStream s_file(&subactivitysuggestionfile);
    ui->textBrowser_2->setText(s_file.readAll());
    subactivitysuggestionfile.close();


}

void useractivity_file::on_ConfirmSubActivity_clicked()                       //push Button to Confirm Sub_Activity
{
    subactivityid = ui->lineEdit_3->text();                                  //Input the sub_activity_id


     //display data to user file part

     QFile userfile(userid_file);
     if(!userfile.open(QFile::WriteOnly|QFile::Append)){
         QMessageBox::information(this,"File",userfile.errorString());            //Dialouge Box if there is error in opening of file
     }
     QTextStream r_file(&userfile);
     r_file<<subactivityid<<" - ";                                           //output the sub_activity_id in the .csv file
     userfile.close();                                                      //close the file


     //Suggestion part begins

     QSet<QString>set;

     QVector<QString>new_data;

     for(int i=1;i<10;i++)
     {
         for(int j=0;j<10;j++)
         {
             QVector<QString>s_data;
             QString id=QString::number(i);
             QString id1=QString::number(j);
             QString uid;
             uid="C:/Users/hp/Documents/QT1/" + id +"_"+id1+".csv";
             QFile ufile(uid);
             if(ufile.exists()&&uid!=userid_file)
             {
                 QFile uidfile(uid);
                 if(!uidfile.open(QIODevice::ReadOnly)){
                     QMessageBox::information(this,"File",uidfile.errorString());        //Dialouge Box if there is error in opening of file
                 }
                 QTextStream u_file(&uidfile);
                 while(!u_file.atEnd())
                 {
                     s_data.push_back(u_file.readLine());
                 }

                 for(int x=1;x<s_data.size();x++)
                 {

                         int comma=0,sub=0,check=0;

                         QString udata=s_data[x];                               //store file line by line
                         std::string s=udata.toStdString();
                         std::string w1;
                         std::stringstream iss1;
                         iss1.str(s);
                         while(iss1>>w1)                       //user1 line  content word by word
                         {
                             if(comma==2&&w1!="-")
                             {
                                 if(check==1)
                                 {

                                     QString d1=QString::fromStdString(w1);
                                     if(!set.contains(d1))
                                     {
                                     new_data.push_back(d1);
                                     set.insert(d1);
                                     }
                                     break;
                                 }
                                 sub++;
                                 if(sub==subactivity)
                                 {
                                     QString d=QString::fromStdString(w1);
                                     if(d==subactivityid)
                                     {
                                         check=1;
                                     }

                                 }



                             }
                             if(w1==",")             //if line contain , don't proceed
                             {
                                 comma++;
                             }
                         }

                     }
                     uidfile.close();
             }
         }
     }


     //storing of data part begins

     QFile subactivitysuggestionfile("C:\\Users\\hp\\Documents\\QT1\\suggestions_sub-activities.txt");
     if(!subactivitysuggestionfile.open(QIODevice::WriteOnly|QIODevice::Text)){
         QMessageBox::information(this,"File",subactivitysuggestionfile.errorString());              //Dialouge Box if there is error in opening of file
     }
     QTextStream s_file(&subactivitysuggestionfile);
     for(int i=0;i<new_data.size();i++)
     {
         s_file<<new_data[i]<<endl;
     }
     subactivitysuggestionfile.close();                                                          //close the file


}
