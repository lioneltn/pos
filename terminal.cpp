#include "terminal.h"
#include <iostream>
#include <windows.h>
#include <lmcons.h>
#include <QSqlQuery>
#include <QtSql>
#include "functions.h"
using namespace std;



Terminal::Terminal(){
    QSqlQuery query;
    query.prepare("SELECT MAX(ID_CAISSE)+1 FROM CAISSE");
    query.exec();
    while (query.next()) {
           ID = query.value(0).toInt();
          }

name=getcomputername();
}

void Terminal::setID(int ID1){
    ID=ID1;

}

int Terminal::getID(){
    return ID;
}

void Terminal::setName(QString name1){
    name=name1;
}

QString Terminal::getName(){
    return name;
}

bool Terminal::saveTerminal(){
    QSqlQuery query;
    bool done=false;
    query.prepare("INSERT INTO CAISSE (ID_CAISSE,NOM) "
                  "VALUES(:id,:nom)");
    query.bindValue(":id",getID());
    query.bindValue(":nom",getName());
    query.exec();
    if (query.numRowsAffected()>0){
        done=true;

    }
    return done;

}


