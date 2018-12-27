#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include <QWidget>
#include "ProgressCircle.h"
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include "pos.h"
#include <QVector>
namespace Ui {
class Productform;
}

class Productform : public QWidget
{
    Q_OBJECT

public:
    explicit Productform(class pos *p,QWidget *parent = nullptr);
    ~Productform();
    void setIDD(int i);
    int getIDD();
    ProgressCircle * progressCircle;
    class pos *p;
    Ui::Productform *ui;
    int id;
signals:
    int signalID(int);
public slots:
    bool sendID();

private slots:
    void on_add_clicked();



private:
    QVector <class pos*> vPos;
    QLabel * label;
};

#endif // PRODUCTFORM_H
