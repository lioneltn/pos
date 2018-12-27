#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
class Payment
{
public:
    Payment();
    ~Payment();
    Payment(float amount1);
    void setAmount(float amount1);
    float getAmount();
    void setState(QString state1);
    QString getState();
    QString getName();



private:
    float amount;
    QString name;
    QString state;

};

#endif // PAYMENT_H
