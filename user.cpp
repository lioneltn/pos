#include "user.h"
#include "functions.h"
#include <QtSql>
#include "SmtpMime"
#include "src/SmtpMime"


using namespace std;

User::User()
{   ID=0;
    email="";
    name="";
    surname="";
    password="";
    photo="";


}

User::User(QString email1,QString name1,QString surname1,QString password1,QString photo1){

            QSqlQuery query;

            query.prepare("SELECT MAX(ID_EMP)+1 FROM EMPLOYER");
            query.exec();
            while (query.next()) {
                   ID = query.value(0).toInt();
                  }
    email=email1;
    name=name1;
    surname=surname1;
    password=password1;
    photo=photo1;





}



bool  User::updateEmail(QString email1){


    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("UPDATE EMPLOYER SET EMAIL=:email WHERE ID_EMP=:id");

    query.bindValue(":email", email1);
    query.bindValue(":id",ID);
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;
    }

return done;

}

bool User::updateName(QString name1){



    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("UPDATE EMPLOYER SET NOM=:name WHERE ID_EMP=:id");
    query.bindValue(":name", name1);
    query.bindValue(":id",ID);
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;
    }

return done;
}


bool User::updateSurname(QString surname1){



    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("UPDATE EMPLOYER SET PRENOM=:surname WHERE ID_EMP=:id");
    query.bindValue(":surname", surname1);
    query.bindValue(":id",ID);
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;
    }

return done;


}

bool User::updatePassword(QString password1){

    QString hashed_password=crypto(password1);
    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("UPDATE EMPLOYER SET MOT_DE_PASSE=:password WHERE ID_EMP=:id");
    query.bindValue(":password", hashed_password);
    query.bindValue(":id",ID);
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;
    }

return done;

}

bool User::updatePhoto(QString photo1){

    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("UPDATE EMPLOYER SET PHOTO=:photo WHERE ID_EMP=:id");
    query.bindValue(":photo", photo1);
    query.bindValue(":id",ID);
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;
    }

return done;


}


int User::fetchID(QString email1){

    QSqlQuery query;
    email=email1;
    query.prepare("SELECT ID_EMP FROM EMPLOYER WHERE EMAIL=:email");
    query.bindValue(":email", email);
    query.exec();
    while(query.next()){
    ID=query.value(0).toInt();
            }
    return ID;
}

QString User::fetchName(int ID1){

    QSqlQuery query;

    query.prepare("SELECT NOM FROM EMPLOYER WHERE ID_EMP=:id");
    query.bindValue(":id", ID1);
    query.exec();
    while(query.next()){
    name=query.value(0).toString();
            }

    return name;

}

QString User::fetchSurname(int ID1){

    QSqlQuery query;

    query.prepare("SELECT PRENOM FROM EMPLOYER WHERE ID_EMP=:id");
    query.bindValue(":id", ID1);

    query.exec();
    while(query.next()){
    surname=query.value(0).toString();
            }
    return surname;

}

QString User::fetchPassword(int ID1){

    QSqlQuery query;

    query.prepare("SELECT MOT_DE_PASSE FROM EMPLOYER WHERE ID_EMP=:id");
    query.bindValue(":id", ID1);

    query.exec();
    while(query.next()){
    password=query.value(0).toString();
            }
    return password;

}



QString User::fetchPhoto(int ID1){

    QSqlQuery query;

    query.prepare("SELECT PHOTO FROM EMPLOYER WHERE ID_EMP=:id");
    query.bindValue(":id", ID1);

    query.exec();
    while(query.next()){
    photo=query.value(0).toString();
            }
    return photo;

}



//Getters
int User::getID(){return ID;
          }
QString User::getName(){
    return name;
}

QString User::getSurname(){
    return surname;
}

QString User::getPassword(){
    return password;
}

QString User::getPhoto(){
    return photo;
}

QString User::getEmail(){
    return email;
}
//Setters
void User::setID(int ID1){
    ID=ID1;
}

void User::setName(QString name1){
    name=name1;
}

void User::setSurname(QString surname1){
    surname=surname1;
}

void User::setPassword(QString password1){
    password=password1;
}

void User::setEmail(QString email1){
    email=email1;
}

void User::setPhoto(QString photo1){
    photo=photo1;
}

//Send Email
bool User::sendEmail(QString email,QString name,QString surname){

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and password
    // for smtp authentification.

    smtp.setUser("amin.haddad@esprit.tn");
    smtp.setPassword("Lionel123");

    // Now we create a MimeMessage object. This is the email.

    MimeMessage message;

    EmailAddress sender("amin.haddad@esprit.tn", "Smarket");
    message.setSender(&sender);
    QString fullName=name+" " +surname;
    EmailAddress to(email, fullName);
    message.addRecipient(&to);

    message.setSubject("Your Account Information");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;
    MimeText text1;
    MimeText text2;
    MimeText text3;


    text1.setText("Your email is: ");
    text2.setText(getEmail());
    text3.setText("\n");

    text.setText("Hi,\nThis is your account informations.\n");

    // Now add it to the mail

    message.addPart(&text);
    message.addPart(&text1);
    message.addPart(&text2);
    message.addPart(&text3);

    // Now we can send the mail

    if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;
        return false;


    }


    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;
        return false;

    }

    if (!smtp.sendMail(message)) {
        qDebug() << "Failed to send mail!" << endl;
        return false;
    }
    else{
    smtp.quit();

    return true;
    }


}

//Signup
bool User::signup(){
    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("INSERT INTO EMPLOYER (ID_EMP,NOM,PRENOM,MOT_DE_PASSE,EMAIL,PHOTO)"
                  "VALUES(:id,:nom,:prenom,:password,:email,:photo)");
    query.bindValue(":id",getID());
    query.bindValue(":nom",getName());
    query.bindValue(":prenom",getSurname());
    query.bindValue(":password",crypto(getPassword()));
    query.bindValue(":email",getEmail());
    query.bindValue(":photo",getPhoto());

    query.exec();
    if (query.numRowsAffected()>0){
        done=true;

    }
    return done;



}



