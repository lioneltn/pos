#ifndef USER_H
#define USER_H
#include <QDialog>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class User
{
private:
    int ID;
    QString email;
    QString name;
    QString surname;
    QString password;
    QString photo;

public:
    User();
    User(QString email1,QString name1,QString surname1,QString password1,QString photo1);


    bool updateEmail(QString email1);
    bool updateName(QString name1);
    bool updateSurname(QString surname1);
    bool updatePassword(QString password1);
    bool updatePhoto(QString photo1);


    int fetchID(QString email1);
    QString fetchName(int ID1);
    QString fetchSurname(int ID1);
    QString fetchPassword(int ID1);
    QString fetchPhoto(int ID1);

    //Getter
    int getID();
    QString getEmail();
    QString getName();
    QString getSurname();
    QString getPassword();
    QString getPhoto();
    //Setters
    void setEmail(QString email1);
    void setID(int ID1);
    void setName(QString name1);
    void setSurname(QString surname1);
    void setPassword(QString password1);
    void setPhoto(QString photo1);



    //Register User//
    bool signup();

    bool sendEmail(QString email,QString name,QString surname);





};

#endif // USER_H
