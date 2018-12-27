#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
using namespace std;
#include <string>
#include <QDialog>


bool isvalidEmail(string email);

//Check User exists
bool checkUser(QString email);
bool login(QString email,QString password);
QString crypto(QString pass);

QString getcomputername();
template < typename T>

int findInVector(const vector<T>  & vecOfElements, const T  & element);

int fetchNbrVente(int ID);

#endif // FUNCTIONS_H
