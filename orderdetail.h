#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include <QDialog>
class OrderDetail
{

private:
    int ID;
    int ID_PRODUIT;
    int ID_COM;
    QString name;
    QString desc;
    QString photo;
    int Qte;
    float price;
    float total;


public:
    OrderDetail();
    OrderDetail(int ID_produit,int ID_com);
    void setQte(int Qte1);
    void setTotal(float total1);
    int getID();
    int getIDCom();
    int getIDProduit();
    int getQte();
    QString getDesc();
    float getPrice();
    float getTotal();
    QString getName();
    QString getPhoto();
    ~OrderDetail();

};

#endif // ORDERDETAIL_H
