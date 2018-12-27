#include "orderdetail.h"
#include <cstdlib>
#include <QSqlQuery>
#include <QtSql>


OrderDetail::OrderDetail()
{

}

OrderDetail::OrderDetail(int ID_produit,int ID_com){

    ID= (rand() % 100) + 1;
    ID_PRODUIT=ID_produit;
    ID_COM=ID_com;
    //GET NAME
    QSqlQuery query;
    query.prepare("SELECT NOM FROM PRODUIT WHERE ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);
    query.exec();

    while (query.next()) {
           name = query.value(0).toString();
          }
    //GET DESCRIPTION
    query.prepare("SELECT DESCRIPTION FROM PRODUIT WHERE"
                  "ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);

    query.exec();
    while (query.next()) {
           desc = query.value(0).toString();
          }

    //GET PHOTO
    query.prepare("SELECT PHOTO FROM PRODUIT WHERE"
                  "ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);

    query.exec();
    while (query.next()) {
           photo = query.value(0).toString();
          }

    //
    //GET PRICE

    query.prepare("SELECT PRIX FROM PRODUIT WHERE"
                  "ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);

    query.exec();
    while (query.next()) {
           price = query.value(0).toInt();
          }
    //

    Qte=1;
    total=price*Qte;

  }

void OrderDetail::setQte(int Qte1){
    Qte+=Qte1;
}

void OrderDetail::setTotal(int Qte1){
    total=Qte1*getPrice();
}

int OrderDetail::getID(){
    return ID;
}

int OrderDetail::getIDProduit(){
    return ID_PRODUIT;
}

int OrderDetail::getQte(){
    return Qte;
}

QString OrderDetail::getDesc(){
    return desc;
}

float OrderDetail::getPrice(){
    return price;
}

float OrderDetail::getTotal(){
    return total;
}

QString OrderDetail::getName(){
    return name;
}

QString OrderDetail::getPhoto(){
    return photo;
}

int OrderDetail::getIDCom(){
    return ID_COM;
}


