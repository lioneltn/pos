#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("smarket");
db.setUserName("Lionel");//inserer nom de l'utilisateur
db.setPassword("Lionel123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
