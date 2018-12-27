#include "payment.h"

Payment::Payment()
{
amount=0;
}

Payment::Payment(float amount1){
    amount=amount1;
}

void Payment::setAmount(float amount1){
    amount=amount1;
}
float Payment::getAmount(){
    return amount;
};
void Payment::setState(QString state1){
    state=state1;
}
QString Payment::getState(){
    return state;
}

Payment::~Payment(){

}
