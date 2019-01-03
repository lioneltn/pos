#ifndef CLIENT_H
#define CLIENT_H
#include <QDialog>

class Client
{
public:
    Client();
    Client(int ID1);
    QString getName();
    QString getSurname();
    QString getAddress();
    QString getTel();
    int getID();
    int getPt();
    QString getEmail();
    void setPt(int pt1);
    void updatePt(int pt1,int ID);
    ~Client();
    QString getPhoto();

private:
    QString name;
    QString surname;
    QString address;
    QString telephone;
    int ID;
    int pt;
    QString email;
    QString photo;


};

#endif // CLIENT_H
