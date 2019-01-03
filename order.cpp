#include "order.h"
#include "order.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QtSql>


Order::Order()
{
OrderDetail *OD=new OrderDetail();

}

Order::Order(int id_client,int id_emp,int id_caisse)
{
TOTAL=0;
QSqlQuery query;
query.prepare("SELECT ID_COM+1 FROM COMMANDE_TMP WHERE ID_CLIENT=:idc");
query.bindValue(":idc",id_client);
query.exec();
while (query.next()) {
       ID=query.value(0).toInt();
      }

ID_EMP=id_emp;
CLIENT_ID=id_client;
ID_CAISSE=id_caisse;
DATE=QDateTime::currentDateTime().toString("dddd dd MMMM yyyy");
//**Populating Order Detail**//
query.prepare("SELECT * FROM DETAIL_COMMANDE_TMP WHERE ID_COM=:id");
query.bindValue(":id",ID);
query.exec();
while(query.next()){
    int ID_PRODUIT;
    ID_PRODUIT=query.value(1).toInt();


    OrderDetail *OD= new OrderDetail(ID_PRODUIT,ID);
    OD->setQte(query.value(2).toInt());
    OD->setTotal(OD->getQte()*static_cast<float>(OD->getPrice()));
    TOTAL=TOTAL+OD->getTotal();

    vDetails.push_back(OD);
}

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

int Order::getCLientID()
{
    return CLIENT_ID;
}

float Order::getTotal()
{
    return TOTAL;
}

bool Order::ClearData()
{   bool done=false;
    bool done1=false;
    QSqlQuery query;
    query.prepare("DELETE FROM DETAIL_COMMANDE_TMP WHERE ID_COM=:id_com");
    query.bindValue(":id_com",getID());
    query.exec();
    if (query.numRowsAffected()>0){
        done1=true;

    }
    else {
        done1=false;
    }
    bool done2=false;
    query.prepare("DELETE FROM COMMANDE_TMP WHERE ID_COM=:id_com");
    query.bindValue(":id_com",getID());
    query.exec();
    if (query.numRowsAffected()>0){
        done1=true;

    }
    else {
        done1=false;
    }

    if (done1 && done2){
        done=true;
    }
    return done;
}

void Order::setTotal(float total1)
{
    TOTAL=total1;
}

Order::~Order()
{
    for (unsigned j=0;j<vDetails.size();j++)
       {
           delete vDetails[j];
       }
    vDetails.clear();
}

void Order::addProduct(OrderDetail *e){
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

    query.prepare("INSERT INTO DETAIL_COMMANDE (ID,ID_PRODUIT,QTE,ID_COM)"
                  "VALUES(:id,:id_produit,:qte,:id_com)");
    query.bindValue(":id",vDetails[i]->getID());
    query.bindValue(":id_produit",vDetails[i]->getIDProduit());
    query.bindValue(":qte",vDetails[i]->getQte());

    query.bindValue(":id_com",vDetails[i]->getIDCom());


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

