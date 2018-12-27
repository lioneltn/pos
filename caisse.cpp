#include "caisse.h"
#include "ui_caisse1.h"
#include "connection.h"
#include <unistd.h>
#include "terminal.h"
#include "SmtpMime"
#include "functions.h"
#include "user.h"


Caisse::Caisse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Caisse)
{
    ui->setupUi(this);
    QPixmap pix(":/img/back.png");
    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);


    //Setting Oval Pic//
    QPixmap oval(":/img/Oval_3.png");
    QPixmap ovalred(":/img/Oval_4.png");
    QPixmap ovalgreen(":/img/green.png");
    QPixmap eye(":/img/show1.png");
    ui->label_4->setPixmap(oval);
    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    QPalette palette1;
    palette1.setBrush(ui->pushButton->backgroundRole(), QBrush(eye));

    ui->pushButton->setPalette(palette1);
    QPixmap footer(":/img/Rectangle_12.png");
    ui->label_6->setPixmap(footer);
    QPixmap user(":/img/icons_user.png");
    ui->label_8->setPixmap(user);
    QPixmap pass(":/img/Stroke_1.png");
    ui->label_11->setPixmap(pass);
    QPixmap logo(":/img/base.png");
    ui->label_13->setPixmap(logo);



    Connection c;
       bool test=c.createconnect();
       if(test){
           ui->round->setPixmap(ovalgreen);

       }
       else {
           ui->status->setText("Disconnected");
           ui->round->setPixmap(ovalred);
       }
     Terminal T1;

    QString a=T1.getName();
    ui->device_id->setText(a);

}

Caisse::~Caisse()
{
    delete ui;
}





void Caisse::on_pushButton_2_clicked()
{
    QString email,password;
    email=ui->lineEdit->text();
    if (isvalidEmail(email.toStdString())){
            password=ui->lineEdit_2->text();

            if (login(email,password)){
                hide();
                pos1=new  class pos(this);
                pos1->show();

                QSqlQuery query;
                query.prepare("INSERT INTO LOGGED (EMAIL) VALUES(:email)");
                query.bindValue(":email",email);

                query.exec();





            }



            else{
                ui->status->setText("Email or password incorrect");
            }
    }
    else  {
        ui->status->setText("Please enter a valid email!");
    }
}


void Caisse::on_device_id_editingFinished()
{
    QString ID1=ui->device_id->text();

    QSqlQuery query;

    query.prepare("INSERT INTO CAISSE VALUES(123)");
    query.bindValue(":id", ID1);
    query.exec();
}





void Caisse::on_pushButton_pressed()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::Normal);

}

void Caisse::on_pushButton_released()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

}

void Caisse::on_pushButton_3_clicked()
{
   hide();
   reset=new Signup(this);
   reset->show();
}

void Caisse::on_pushButton_4_clicked()
{
    hide();
    signup=new Register(this);
    signup->show();
}
