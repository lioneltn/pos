#ifndef POS_H
#define POS_H

#include "order.h"
#include "caisse.h"
#include "functions.h"
#include "session.h"
#include "terminal.h"
#include <QDialog>
#include <QRoundProgressBar.h>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include "user.h"
#include <QVector>
#include <QBoxLayout>
#include "orderdetail.h"
#include "productform.h"
#include "arduino.h"


namespace Ui {
class pos;
}

class pos : public QDialog
{
    Q_OBJECT

public:
    QVector <User*> vUser;
    QVector <Terminal*> vTerminal;
    QVector <Order*> vOrder;
    QVector <OrderDetail*> vDetails;
    QVector <Session*> vSessions;
    QString em;
    explicit pos(QWidget *parent = nullptr);
    void setID(int j);
    int getID();
    int i=0;
    int del;

    ~pos();


public slots:
    bool deleteItem();
    bool receiveID(int);
    bool updateQte();
    bool updateQte2();
    void Result();
signals:
    void mySignal();
private slots:
    void update_label();

    void addIndefinite();



    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_search_clicked();

    void on_text_textChanged(const QString &arg1);

    void on_pushButton_clicked();


    void on_pushButton_5_clicked();



    void on_pushButton_3_clicked();

    void on_cancel_clicked();
    void itemClickedSlot(QListWidgetItem *item2);

    void on_pay_clicked();

    void on_cash_clicked();

    void on_go_back_clicked();

private:


    QByteArray data;
    int x = 0;
    QString result;
    Arduino A;
    Ui::pos *ui;
    void connectToSlider(QRoundProgressBar *bar,int nbr);
};

#endif // POS_H
