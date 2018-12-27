#include "session.h"
#include <QSqlQuery>
#include <QtSql>


Session::Session()
{



}

Session::Session(int id_emp,int id_caisse){
    QSqlQuery query;

    query.prepare("SELECT MAX(ID_SESSION)+1 FROM EMP_SESSION");
    query.exec();
    while (query.next()) {
           ID_SESSION = query.value(0).toInt();
          }
ID_EMP=id_emp;
ID_CAISSE=id_caisse;
NBR_VENTE=0;
TOTAL=0;
DATE=QDateTime::currentDateTime().toString("dddd dd MMMM yyyy");
}

int Session::getID(){
    return ID_SESSION;
}

int Session::getNbrVente(){
    return NBR_VENTE;
}

float Session::getTotal(){
    return TOTAL;
}

void Session::setID(int ID1){
    ID_SESSION=ID1;
}

void Session::setNbrVente(int Nbr){
    NBR_VENTE=Nbr;
}

void Session::setTotal(float total){
    TOTAL=total;
}

int Session::getIDCaisse(){
    return ID_CAISSE;
}

int Session::getIDEmp(){
    return ID_EMP;
}
bool Session::saveSession(){
    QSqlQuery query;
    bool done;
    done=false;
    query.prepare("INSERT INTO EMP_SESSION (ID_SESSION,DATE_SESSION,NBR_VENTE,TOTAL,ID_CAISSE,ID_EMP)"
                  "VALUES(:id,:date,:nbr,:total,:id_caisse,:id_emp)");
    query.bindValue(":id",getID());
    query.bindValue(":date",getDate());
    query.bindValue(":nbr",getNbrVente());
    query.bindValue(":total",getTotal());


    query.bindValue(":id_emp",getIDEmp());
    query.bindValue(":id_emp",getIDCaisse());


    query.exec();
    if (query.numRowsAffected()>0){
        done=true;

    }
    return done;
}


Session::~Session(){

}


QString Session::getDate(){
    return DATE;
}
