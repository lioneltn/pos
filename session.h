#ifndef SESSION_H
#define SESSION_H

#include <QDialog>
class Session
{
public:
    Session();
    ~Session();
    Session(int id_emp,int id_caisse);
    bool saveSession();
    int getID();
    int getNbrVente();
    float getTotal();
    void setID(int ID1);
    void setNbrVente(int Nbr);
    void setTotal(float total);
    QString getDate();
    int getIDEmp();
    int getIDCaisse();



private:
int ID_SESSION;
int ID_EMP;
QString DATE;
int ID_CAISSE;
int NBR_VENTE;
float TOTAL;
};

#endif // SESSION_H
