#ifndef CAISSE_H
#define CAISSE_H

#include <QDialog>
#include "reset.h"
#include "pos.h"
#include "register.h"


namespace Ui {
class Caisse;
}

class Caisse : public QDialog
{
    Q_OBJECT

public:
    explicit Caisse(QWidget *parent = nullptr);
    ~Caisse();

private slots:



    void on_pushButton_2_clicked();

    void on_device_id_editingFinished();



    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
signals:
    void emailChanged(QString);


private:
    Ui::Caisse *ui;
    Signup *reset;
    class pos *pos1;
    Register *signup;
};

#endif // CAISSE_H
