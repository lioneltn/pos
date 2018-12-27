#ifndef CASH_H
#define CASH_H
#include "payment.h"


class Cash:public Payment
{
public:
    Cash();
    ~Cash();

    Cash(float amount);
    float calculateRest(float amount_paid);
    QString getName();

private:
    float rest;
    QString name;

};

#endif // CASH_H
