#include "order.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QtSql>

Order::Order()
{

}

Order::Order(int id_emp,int id_caisse)
{

QSqlQuery query;

query.prepare("SELECT MAX(ID_EMP)+1 FROM EMPLOYER");
query.exec();
while (query.next()) {
       ID = query.value(0).toInt();
      }
ID_EMP=id_emp;
ID_CAISSE=id_caisse;
DATE=QDateTime::currentDateTime().toString("dddd dd MMMM yyyy");
vDetails={};
}

void Order::setID(int ID1){
    ID=ID1;
}
void Order::setID_CAISSE(int ID1){
    ID_CAISSE=ID1;
}

void Order::setID_EMP(int ID1){
    ID_EMP=ID1;
}
QString Order::getDATE(){
    return DATE;
}

int Order::getID(){
    return ID;
}

int Order::getID_CAISSE(){
    return ID_CAISSE;

}

int Order::getID_EMP(){
    return ID_EMP;
}

void Order::setPType(QString type){
    PType=type;
}
QString Order::getPType(){
    return PType;
}

void Order::addProduct(OrderDetail e){
    vDetails.push_back(e);
}

bool Order::removeProduct(unsigned i){
    if(i >= 0 && i < vDetails.size())
        {
            vDetails.erase(vDetails.begin()+ i-1);
            return true;
        }
        else
        {
           return false;
        }

}

bool Order::saveOrderDetail(){
    bool done;
    done=false;
    for(unsigned i=0; i<vDetails.size(); i++){

    QSqlQuery query;

    query.prepare("INSERT INTO COMMANDE (ID,ID_PRODUIT,NOM_PRODUIT,QTE,TOTAL,ID_COM)"
                  "VALUES(:id,:id_produit,:nom,:qte,:total,:id_com)");
    query.bindValue(":id",vDetails[i].getID());
    query.bindValue(":id_produit",vDetails[i].getIDProduit());
    query.bindValue(":nom",vDetails[i].getName());
    query.bindValue(":total",vDetails[i].getTotal());
    query.bindValue(":id_com",vDetails[i].getIDCom());


    query.exec();
    if (query.numRowsAffected()>0){
        done=true;

    }
    else {
        done=false;
    }
    }
return done;

}
bool Order::saveOrder(){
    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("INSERT INTO COMMANDE (ID_COM,DATE_COM,PAYMENT_TYPE,ID_CAISSE,ID_EMP)"
                  "VALUES(:id,:date,:type,:id_caisse,:id_emp)");
    query.bindValue(":id",getID());
    query.bindValue(":date",getDATE());
    query.bindValue(":id_caisse",getID_CAISSE());
    query.bindValue(":type",getPType());


    query.bindValue(":id_emp",getID_EMP());


    query.exec();
    if (query.numRowsAffected()>0){
        done=true;

    }
    return done;

}

