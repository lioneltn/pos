#include "client.h"
#include <QSqlQuery>
#include <QtSql>
Client::Client()
{


}
Client::~Client(){

}
Client::Client(int ID1){
    ID=ID1;


        QSqlQuery query;

        query.prepare("SELECT * FROM CLIENT WHERE ID_CLIENT=:id");
        query.bindValue(":id",ID);
        query.exec();
        while (query.next()) {
               pt=query.value(1).toInt();
               name = query.value(2).toString();
               surname=query.value(3).toString();
               address=query.value(4).toString();
               telephone=query.value(5).toString();
               email=query.value(6).toString();
               photo=query.value(7).toString();

              }




}

QString Client::getAddress(){
    return address;
}

QString Client::getEmail(){
    return email;
}

int Client::getID(){
   return ID;
}

int Client::getPt(){
    return pt;
}

QString Client::getTel(){
    return telephone;
}

QString Client::getName(){
    return name;
}

QString Client::getSurname(){
    return surname;
}

void Client::setPt(int pt1){
    pt=pt1;
}

void Client::updatePt(int pt1,int ID){

    QSqlQuery query;

    query.prepare("UPDATE CLIENT SET PTFID=:pt WHERE ID_CLIENT=:id");
    query.bindValue(":id",ID);
    query.bindValue("pt",pt1);
    query.exec();



}

QString Client::getPhoto(){
    return photo;
}











