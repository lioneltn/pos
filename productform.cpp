#include "productform.h"
#include "ui_productform.h"

Productform::Productform(class pos *p,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Productform)
{
    vPos.push_back(p);
    ProgressCircle * progressCircle;
    ui->setupUi(this);
    setStyleSheet(".QWidget{border-bottom: 1px solid lightgrey;}");
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->setSpacing(12);
    progressCircle = new ProgressCircle();
    progressCircle->setFixedSize(30, 30);
    layout->addWidget(progressCircle);
    label = new QLabel("text");
    layout->addWidget(label, 1);
    QPushButton * closeButton = new QPushButton(tr("Delete"));
    //connecting two ui//
    id=p->getID();
    ui->code->setText(QString::number(id));
    connect(closeButton, &QPushButton::clicked, p, &pos::deleteItem);


    connect(closeButton, &QPushButton::clicked, this, &Productform::sendID);

    connect(closeButton, &QPushButton::clicked, this, &QObject::deleteLater);
    layout->addWidget(closeButton);

    QPropertyAnimation * progressCircleAnimation = new QPropertyAnimation(progressCircle, "outerRadius", progressCircle);
    progressCircleAnimation->setDuration(750);
    progressCircleAnimation->setEasingCurve(QEasingCurve::OutQuad);
    progressCircleAnimation->setStartValue(0.0);
    progressCircleAnimation->setEndValue(1.0);
    progressCircleAnimation->start(QAbstractAnimation::DeleteWhenStopped);


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
    ui->code->setText("Loool");
}

bool Productform::sendID(){
   vPos[0]->del=id;


}
