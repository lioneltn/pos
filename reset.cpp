#include "reset.h"
#include "ui_signup.h"
#include "src/SmtpMime"
#include <QSqlQuery>
#include "src/smtpclient.h"
#include "functions.h"
#include <string>
#include <iostream>


Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    QPixmap pix(":/img/back.png");
    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);

    //Setting Images//
    QPixmap user(":/img/icons_user.png");
    ui->icon->setPixmap(user);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_send_clicked()
{
    QString email;
    email=ui->email->text();

    if (isvalidEmail(email.toStdString())){
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYER WHERE EMAIL=:id");
    query.bindValue(":id", email);

    query.exec();

    if (query.exec()){
            int i=0;
            while(query.next()){
            i++;}

            if(i==1){
                // First we need to create an SmtpClient object
                // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

                SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

                // We need to set the username (your email address) and password
                // for smtp authentification.

                smtp.setUser("amin.haddad@esprit.tn");
                smtp.setPassword("Lionel123");

                // Now we create a MimeMessage object. This is the email.

                MimeMessage message;

                EmailAddress sender("amin.haddad@esprit.tn", "Amin Haddad");
                message.setSender(&sender);

                EmailAddress to(email, "Customer");
                message.addRecipient(&to);

                message.setSubject("Reset Password");

                // Now add some text to the email.
                // First we create a MimeText object.

                MimeText text;

                text.setText("Hi,\nThis is a simple email message.\n");

                // Now add it to the mail

                message.addPart(&text);

                // Now we can send the mail

                if (!smtp.connectToHost()) {
                    qDebug() << "Failed to connect to host!" << endl;
                    ui->error->setText("Failed to connect to host!");

                }


                if (!smtp.login()) {
                    qDebug() << "Failed to login!" << endl;
                    ui->error->setText("Failed to login!");

                }

                if (!smtp.sendMail(message)) {
                    qDebug() << "Failed to send mail!" << endl;
                    ui->error->setText("Failed to send email");

                }
                else{
                    ui->success->setText("We have sent an email to reset your password");


                }

                smtp.quit();


            }
            else if (i==0){
                ui->error->setText("No account found with this email");
            }
            }
}
    else  {
        ui->error->setText("This is not an email address!");
    }
    }
