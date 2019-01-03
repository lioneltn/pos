#include "orderdetail.h"
#include <cstdlib>
#include <QSqlQuery>
#include <QtSql>


OrderDetail::OrderDetail()
{
    ID=0;

}

OrderDetail::OrderDetail(int ID_produit,int ID_com){
    ID_COM=ID_com;
    ID_PRODUIT=ID_produit;

    QSqlQuery query;
    query.prepare("SELECT ID+1 FROM DETAIL_COMMANDE_TMP WHERE ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);
    query.exec();

    while (query.next()) {
           ID=query.value(0).toInt();

          }

    //GET NAME

    query.prepare("SELECT * FROM PRODUIT WHERE ID_PRODUIT=:id");
    query.bindValue(":id",ID_PRODUIT);
    query.exec();

    while (query.next()) {
           name = query.value(1).toString();
           price = query.value(2).toFloat();
           photo = query.value(4).toString();

          }


    Qte=0;
    total=0;


  }

void OrderDetail::setQte(int Qte1){
    Qte=Qte1;
}

void OrderDetail::setTotal(float total1){
    total=total1;
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

OrderDetail::~OrderDetail()
{

}

int OrderDetail::getIDCom(){
    return ID_COM;
}


