#ifndef POS_H
#define POS_H

#include <QDialog>
#include <QRoundProgressBar.h>
#include <QWidget>
#include "productform.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "user.h"
#include <QVector>
#include <QBoxLayout>

namespace Ui {
class pos;
}

class pos : public QDialog
{
    Q_OBJECT

public:

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

private slots:

    void addIndefinite();



    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_search_clicked();

    void on_text_textChanged(const QString &arg1);

    void on_pushButton_clicked();


    void on_pushButton_5_clicked();



    void on_pushButton_3_clicked();

private:
    QVector <User*> vUser;

    Ui::pos *ui;



    void connectToSlider(QRoundProgressBar *bar,int nbr);
};

#endif // POS_H
