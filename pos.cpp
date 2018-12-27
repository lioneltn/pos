#include "pos.h"
#include "ui_pos.h"
#include "caisse.h"
#include "functions.h"
#include "session.h"
#include "terminal.h"
#include <QScrollArea>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "client.h"

pos::pos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pos)
{
    ui->setupUi(this);




    ui->stackedWidget->setCurrentIndex(0);
    QPixmap pix(":/img/pos_back.png");
    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);

    QPixmap user_back(":/img/Rectangle_2.png");
    ui->back_user->setPixmap(user_back);

    QPixmap back(":/img/bg1.png");
    ui->back->setPixmap(back);


    QPixmap bar(":/img/bar.png");
    ui->bar->setPixmap(bar);


    //Starting Terminal
    Terminal terminal;

    //Starting Employer
    QSqlQuery query;
    query.prepare("SELECT * FROM LOGGED");
    query.exec();
    while(query.next()){
    em=query.value(0).toString();
    }

    QString email=em;
    User *user=new User();
    user->setID(user->fetchID(email));
    user->setEmail(email);

    user->setName(user->fetchName(user->getID()));
    user->setSurname(user->fetchSurname(1));
    user->setPhoto(user->fetchPhoto(user->getID()));
    //Adding user to vUser
    vUser.push_back(user);

        ui->label->setText(vUser[0]->getName());

    ui->user_name->setText(vUser[0]->getSurname());

    QString photo1=":"+user->getPhoto();
    QPixmap profile(photo1);
    ui->user_photo->setPixmap(profile);
    ui->user_photo->setScaledContents(true);

    //Starting Session
    Session session(user->getID(),terminal.getID());


    //Circular Progress Bar



    ui->RoundBar1->setDecimals(0);
    ui->RoundBar1->setBarStyle(QRoundProgressBar::StyleLine);
    ui->RoundBar1->setOutlinePenWidth(18);
    ui->RoundBar1->setDataPenWidth(10);
    connectToSlider(ui->RoundBar1,fetchNbrVente(user->getID()));




    ui->RoundBar2->setDecimals(0);
    ui->RoundBar2->setBarStyle(QRoundProgressBar::StyleLine);
    ui->RoundBar2->setOutlinePenWidth(18);
    ui->RoundBar2->setDataPenWidth(10);
    connectToSlider(ui->RoundBar2,session.getNbrVente()+55);

/***Adding Product to List***/

connect(ui->pushButton_6, &QPushButton::clicked, this, &pos::addIndefinite);


}

pos::~pos()
{
    delete ui;
}


bool pos::deleteItem(){


    delete ui->listWidget->takeItem(del-1);
    ui->name->setText(QString::number(del));
    return true;

}

bool pos::receiveID(int id)
{
    ui->name->setText(QString::number(id+20));
}

void pos::setID(int j)
{
    i=j;
}

int pos::getID()
{
    return i;
}



void pos::addIndefinite()
{
    //**Adding Product form to QlistWidget**//

        Productform * item = new Productform(this);
        this->setID(this->getID()+1);





        QListWidgetItem *item1 = new QListWidgetItem();
        item1->setSizeHint(QSize(0,65));



        ui->listWidget->addItem(item1);
        ui->listWidget->setItemWidget(item1,item);



}



void pos::connectToSlider(QRoundProgressBar *bar,int nbr)
{
    bar->setRange(0, 100);
    bar->setValue(nbr);

}

void pos::on_pushButton_2_clicked()
{


ui->stackedWidget->setCurrentIndex(3);
//Getting User ID from Arduino
Client client(1);
//User Info Card
ui->name->setText(client.getName());
ui->ID->setText(QString::number(client.getID()));
ui->ADD->setText(client.getAddress());
ui->EMAIL->setText(client.getEmail());
ui->PHONE->setText(client.getTel());
ui->POINTS->setText(QString::number(client.getPt()));

QString photo1=":"+client.getPhoto();
QPixmap profile(photo1);
ui->clientphoto->setPixmap(profile);
ui->clientphoto->setScaledContents(true);


}

void pos::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void pos::on_search_clicked()
{
    QString search=ui->text->text();
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PRODUIT WHERE NOM='"+search+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRICE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORY"));

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->show();
}

void pos::on_text_textChanged(const QString &arg1)
{
    QString search=ui->search->text();
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT WHERE NOM='"+arg1+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRICE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CATEGORY"));

    ui->tableView->setModel(model);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->show();
}

void pos::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




void pos::on_pushButton_5_clicked()
{
 ui->stackedWidget->setCurrentIndex(1);
}


void pos::on_pushButton_3_clicked()
{
    QString name,surname,email,password;
    name=ui->name_2->text();
    surname=ui->name_3->text();
    email=ui->name_4->text();
    password=ui->name_5->text();


    ui->status->setText(vUser[0]->getName());
    //Updating

    bool done=false;

    if(name.length()!=0){
        if(vUser[0]->updateName(name)){

            done=true;
        }
    }

    if (surname.length()!=0){
        if(vUser[0]->updateSurname(surname)){
            done=true;
        }
    }

    if(password.length()!=0){
        if(vUser[0]->updatePassword(password)){
            done=true;
        }
    }

    if(isvalidEmail(email.toStdString()) && email.length()!=0){
        if(vUser[0]->updateEmail(email)){
        done=true;
        }
    }



    if(done){
        ui->status->setText("Success!");
    }

}


