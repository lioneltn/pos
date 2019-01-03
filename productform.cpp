#include "productform.h"
#include "ui_productform.h"

Productform::Productform(class pos *p,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Productform)
{
    vPos.push_back(p);

    ui->setupUi(this);


    //connecting two ui//
    id=p->getID();


    ui->product_name->setText(p->vOrder[0]->vDetails[id]->getName());
    ui->product_id->setText(QString::number(p->vOrder[0]->vDetails[id]->getIDProduit()));
    ui->product_price->setText(QString::number(p->vOrder[0]->vDetails[id]->getPrice()));
    ui->product_qte->setText(QString::number(p->vOrder[0]->vDetails[id]->getQte()));

    connect(ui->closeButton, &QPushButton::clicked, this, &Productform::sendID);
    connect(ui->closeButton, &QPushButton::clicked, p, &pos::deleteItem);
    connect(ui->closeButton, &QPushButton::clicked, this, &QObject::deleteLater);
    connect(ui->add, &QPushButton::clicked, this, &Productform::sendID);

    connect(ui->add,&QPushButton::clicked,p,&pos::updateQte);

    connect(ui->remove, &QPushButton::clicked, this, &Productform::sendID);

    connect(ui->remove,&QPushButton::clicked,p,&pos::updateQte2);




}

void finish(bool success)
{
    ProgressCircle * progressCircle;
    QLabel * label;

    QPropertyAnimation * animation = new QPropertyAnimation(progressCircle, "outerRadius", progressCircle);
    animation->setDuration(1500);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setEndValue(0.5);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    animation = new QPropertyAnimation(progressCircle, "innerRadius", progressCircle);
    animation->setDuration(750);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QColor color = success ? QColor(155,219,58) : QColor(255,100,100);

    animation = new QPropertyAnimation(progressCircle, "color", progressCircle);
    animation->setDuration(750);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setEndValue(color);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    label->setText(success ? "Successfully finished" : "Aborted");
}

Productform::~Productform()
{
    delete ui;

}

void Productform::setIDD(int i)
{
    id=i;
}

int Productform::getIDD()
{
    return id;
}

void Productform::on_add_clicked()
{
    vPos[0]->vOrder[0]->vDetails[id]->setQte(vPos[0]->vOrder[0]->vDetails[id]->getQte()+1);
    int qte=vPos[0]->vOrder[0]->vDetails[id]->getQte();
    ui->product_qte->setText(QString::number(qte));
}

bool Productform::sendID(){
   vPos[0]->del=id;



}

void Productform::on_remove_clicked()
{
    vPos[0]->vOrder[0]->vDetails[id]->setQte(vPos[0]->vOrder[0]->vDetails[id]->getQte()-1);
    int qte=vPos[0]->vOrder[0]->vDetails[id]->getQte();
    ui->product_qte->setText(QString::number(qte));
}
