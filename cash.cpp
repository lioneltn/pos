#include "cash.h"

Cash::Cash()
{
rest=0;
}

Cash::Cash(float amount):Payment(amount){
    rest=0;
    name="Cash";
}

float Cash::calculateRest(float amount_paid){
    rest=amount_paid-getAmount();
    return rest;
}

QString Cash::getName(){
    return name;
}

Cash::~Cash(){

}
