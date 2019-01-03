#include "pos.h"
#include "ui_pos.h"
#include <QScrollArea>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "client.h"
#include <QMovie>
#include "calc.h"
#include <QDateTime>


pos::pos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pos)
{
    ui->setupUi(this);
    QString DATE=QDateTime::currentDateTime().toString("dddd dd MMMM yyyy");
    QString TIME=QDateTime::currentDateTimeUtc().toString();
    ui->date->setText(DATE);
    ui->time->setText(TIME);

    //**Adding Loading Gif to load Label**//
    QMovie *movie = new QMovie(":/img/loading.gif");
    ui->load->setMovie(movie);
    ui->load->show();
    movie->start();



    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    QPixmap pix(":/img/pos_back.png");
    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);

    QPixmap user_back(":/img/Rectangle_2.png");
    ui->back_user->setPixmap(user_back);

    QPixmap back(":/img/bg1.png");
    ui->back->setPixmap(back);





    //Starting Terminal
    Terminal *terminal=new Terminal();
    vTerminal.push_back(terminal);

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
    Session *session =new Session(user->getID(),terminal->getID());
    vSessions.push_back(session);


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
    connectToSlider(ui->RoundBar2,session->getNbrVente());

/***Adding Product to List***/



connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(itemClickedSlot(QListWidgetItem*)));

}






bool pos::receiveID(int id)
{
    ui->name->setText(QString::number(id+20));
}

bool pos::updateQte()
{
   this->vOrder[0]->vDetails[del]->setTotal(this->vOrder[0]->vDetails[del]->getQte()*this->vOrder[0]->vDetails[del]->getPrice());
   float new_total=(this->vOrder[0]->getTotal())+(this->vOrder[0]->vDetails[del]->getPrice());
   this->vOrder[0]->setTotal(new_total);
   ui->total_int->setText(QString::number(this->vOrder[0]->getTotal()));

   float vat=this->vOrder[0]->getTotal()*21/100;
   float subtotal=this->vOrder[0]->getTotal()-vat;
   ui->subtotal_int->setText(QString::number(subtotal));
   ui->vat_int->setText(QString::number(vat));


}

bool pos::updateQte2()
{
    this->vOrder[0]->vDetails[del]->setTotal(this->vOrder[0]->vDetails[del]->getQte()*this->vOrder[0]->vDetails[del]->getPrice());
    float new_total=(this->vOrder[0]->getTotal())-(this->vOrder[0]->vDetails[del]->getPrice());
    this->vOrder[0]->setTotal(new_total);
    ui->total_int->setText(QString::number(this->vOrder[0]->getTotal()));

    float vat=this->vOrder[0]->getTotal()*21/100;
    float subtotal=this->vOrder[0]->getTotal()-vat;
    ui->subtotal_int->setText(QString::number(subtotal));
    ui->vat_int->setText(QString::number(vat));

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

       /* Productform * item = new Productform(this);
        this->setID(this->getID()+1);





        QListWidgetItem *item1 = new QListWidgetItem();
        item1->setSizeHint(QSize(0,65));



        ui->listWidget->addItem(item1);
        ui->listWidget->setItemWidget(item1,item);


*/
}



void pos::connectToSlider(QRoundProgressBar *bar,int nbr)
{
    bar->setRange(0, 100);
    bar->setValue(nbr);

}



void pos::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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

void pos::on_pushButton_2_clicked()
{

ui->stackedWidget->setCurrentIndex(3);
//Connecting to Arduino
int ret=A.connect_arduino(); // lancer la connexion à arduino
switch(ret){
case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
    break;
case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
case(-1):qDebug() << "arduino is not available";
}


 //END ARDUINO//
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
QObject::connect(this,SIGNAL(mySignal()),this,SLOT(Result()));






}

void pos::on_cancel_clicked()
{
    QObject::connect(this,SIGNAL(mySignal()),this,SLOT(Result()));
    result="";

    i=0;
    ui->verticalLayout->takeAt(0);

    for (int j=0;j<=ui->listWidget->count();j++)
       {
           delete ui->listWidget->takeItem(j);
       }
    for (unsigned j=0;j<this->vOrder.size();j++)
       {
           delete this->vOrder[j];
       }
    vOrder.clear();

    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void pos::itemClickedSlot(QListWidgetItem *item2)
{
    int currentRow = ui->listWidget->currentRow();


    QString photo=":"+this->vOrder[0]->vDetails[currentRow]->getPhoto();
    QPixmap product(photo);
    ui->product_photo->setPixmap(product);
    ui->product_photo->setScaledContents(true);
    ui->product_name->setText(this->vOrder[0]->vDetails[currentRow]->getName());
    ui->product_price->setText(QString::number(this->vOrder[0]->vDetails[currentRow]->getPrice()));
    ui->qte->setText((QString::number(this->vOrder[0]->vDetails[currentRow]->getQte())));
    ui->price_int->setText(QString::number(this->vOrder[0]->vDetails[currentRow]->getPrice()));


}

bool pos::deleteItem(){


    delete ui->listWidget->takeItem(del);

    this->vOrder[0]->setTotal((this->vOrder[0]->getTotal())-(this->vOrder[0]->vDetails[del]->getTotal()));
    ui->total_int->setText(QString::number(this->vOrder[0]->getTotal()));
    i=i-1;
    float vat=this->vOrder[0]->getTotal()*21/100;
    float subtotal=this->vOrder[0]->getTotal()-vat;
    ui->subtotal_int->setText(QString::number(subtotal));
    ui->vat_int->setText(QString::number(vat));

    return true;

}
pos::~pos()
{
    delete ui;

    for (unsigned j=0;j<vOrder.size();j++)
       {
           delete this->vOrder[j];
       }
    vOrder.clear();
    for (unsigned j=0;j<vTerminal.size();j++)
       {
           delete this->vTerminal[j];
       }
    vTerminal.clear();
    for (unsigned j=0;j<vUser.size();j++)
       {
           delete this->vUser[j];
       }
    vUser.clear();

}

void pos::on_pay_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void pos::Result()
{
    QObject::disconnect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
QObject::disconnect(this,SIGNAL(mySignal()),this,SLOT(Result()));


ui->name->setText("Detected");

ui->stackedWidget->setCurrentIndex(5);
//Adding Calculator

    Calc *calculator=new Calc();
    ui->verticalLayout->addWidget(calculator);


ui->stackedWidget_2->setCurrentIndex(1);
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
//End of User Info Card

//Starting New Order//
Order *new_order=new Order(client.getID(),vUser[0]->getID(),vTerminal[0]->getID());
vOrder.push_back(new_order);
ui->name->setText(QString::number(vOrder.size()));
//Setting Total
ui->total_int->setText(QString::number(this->vOrder[0]->getTotal()));
float vat=this->vOrder[0]->getTotal()*21/100;
float subtotal=this->vOrder[0]->getTotal()-vat;
ui->subtotal_int->setText(QString::number(subtotal));
ui->vat_int->setText(QString::number(vat));

//Populating Product List//

for (unsigned j=0;j<this->vOrder[0]->vDetails.size();j++){
Productform * item = new Productform(this);

QListWidgetItem *item1 = new QListWidgetItem();
item1->setSizeHint(QSize(0,50));



ui->listWidget->addItem(item1);
ui->listWidget->setItemWidget(item1,item);

i=i+1;
}
result="";
}


void pos::update_label()
{

    data=A.read_from_arduino();
    result+=QString::fromStdString(data.toStdString());
    qDebug() << result;
    emit mySignal();

}

void pos::on_cash_clicked()
{
    vOrder[0]->setPType("Cash");
    if(vOrder[0]->saveOrderDetail()){
        qDebug() << "Order Detail Saved";
    }
    if (vOrder[0]->saveOrder()){
        qDebug() << "Order Saved";
    }
    if (vOrder[0]->ClearData()){
        qDebug() << "Data Cleared";
    }
    vSessions[0]->setNbrVente(vSessions[0]->getNbrVente()+1);

    connectToSlider(ui->RoundBar2,vSessions[0]->getNbrVente());


    ui->stackedWidget->setCurrentIndex(0);

}

void pos::on_go_back_clicked()
{
    ui->stackedWidget->set
}
