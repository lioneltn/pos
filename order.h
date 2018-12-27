#ifndef ORDER_H
#define ORDER_H
#include <QDialog>
#include <vector>
#include <orderdetail.h>
using namespace std;

class Order
{
public:
    Order();
    Order(int id_emp,int id_caisse);
    bool placeOrder();
    bool saveOrder();
    void setID(int ID1);
    void setID_EMP(int ID_EMP1);
    void setID_CAISSE(int ID_CAISSE1);
    int getID();
    int getID_CAISSE();
    int getID_EMP();
    QString getDATE();
    void addProduct(OrderDetail e);
    bool removeProduct(unsigned i);
    bool saveOrderDetail();
    void setPType(QString type);
    QString getPType();






private:

    int ID;
    int ID_EMP;
    int ID_CAISSE;
    QString DATE;
    vector <OrderDetail> vDetails ;
    QString PType;


};

#endif // ORDER_H
