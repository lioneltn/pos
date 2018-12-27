#include <iostream>
#include <regex>
#include "functions.h"
#include <string>
#include <QSqlQuery>
#include <QDialog>
#include <QtSql>
#include <QCryptographicHash>
#include <QByteArray>
#include <QFileDialog>
#include <QSqlQuery>
#include <QtSql>

#include <windows.h>
#include <lmcons.h>

using namespace std;

QString getcomputername(){

    //GET COMPUTER NAME//
TCHAR computername[UNLEN+1];
DWORD computername_len=UNLEN+1;
GetComputerName((TCHAR*)computername,&computername_len);
wstring ID1(&computername[0]);
QString name=QString::fromStdWString(ID1);
return name;
}
bool isvalidEmail(string email)
{
const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
return regex_match(email,pattern);
}

bool login(QString email,QString password){
    QSqlQuery query;
    bool found=false;
    query.prepare("SELECT * FROM EMPLOYER WHERE EMAIL=:email AND MOT_DE_PASSE=:password");
    query.bindValue(":email",email);
    query.bindValue(":password",crypto(password));





    query.exec();
    if (query.exec()){
            int i=0;
            while(query.next()){
            i++;
}
            if (i==1){
                found=true;
            }

}
    return found;
}


QString crypto(QString password){
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
    QString out=hashed.toHex();
    return out;
}

bool checkUser(QString email){
    QSqlQuery query;
    bool found=false;
    query.prepare("SELECT * FROM EMPLOYER WHERE EMAIL=:email");
    query.bindValue(":email",email);
    query.exec();
    if (query.exec()){
            int i=0;
            while(query.next()){
            i++;
}
            if (i==1){
                found=true;
            }

}
    return found;
}


//Search element in Vector
template < typename T>

int findInVector(const vector<T>  & vecOfElements, const T  & element){
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    int result=0;
    if (it != vecOfElements.end())
        {
            int result = distance(vecOfElements.begin(), it);
    }
    return result ;
}


int fetchNbrVente(int ID){
    QSqlQuery query;
    int Nbr=0;
    query.prepare("SELECT NBR_VENTE FROM EMP_SESSION WHERE ID_EMP=:id");
    query.bindValue(":id",ID);
    query.exec();

    while(query.next()){
        Nbr=query.value(0).toInt();
    }
return Nbr;

}
