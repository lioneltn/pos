#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QGraphicsScene>
#include "user.h"


namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_email_editingFinished();

    void on_email_selectionChanged();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_upload_clicked();

private:
    Ui::Register *ui;

    QPixmap image;

    QImage  *imageObject;

    QGraphicsScene *scene;


};

#endif // REGISTER_H
