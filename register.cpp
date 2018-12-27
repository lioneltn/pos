#include "register.h"
#include "ui_register.h"
#include "functions.h"
#include <QFileDialog>


Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QPixmap pix(":/img/back.png");
    QPixmap eye(":/img/show1.png");

    pix = pix.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);

    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    QPalette palette1;
    palette1.setBrush(ui->pushButton->backgroundRole(), QBrush(eye));
    ui->pushButton->setPalette(palette1);

    QPixmap user(":/img/icons_user.png");
    ui->user_icon->setPixmap(user);
    ui->user_icon_2->setPixmap(user);
    ui->user_icon_3->setPixmap(user);


    QPixmap pass(":/img/Stroke_1.png");
    ui->password_icon->setPixmap(pass);
}

Register::~Register()
{
    delete ui;
}
QString filePath;
void Register::on_pushButton_pressed()
{
    ui->password->setEchoMode(QLineEdit::Normal);

}

void Register::on_pushButton_released()
{
    ui->password->setEchoMode(QLineEdit::Password);

}

void Register::on_email_editingFinished()
{
    QString email=ui->email->text();
    if(checkUser(email)){
    ui->status->setText("A user with email already exists!");
    }
    if (!(isvalidEmail(email.toStdString()))){
        ui->status->setText("This is not a valid email!");

    }

}

void Register::on_email_selectionChanged()
{

}

void Register::on_pushButton_2_clicked()
{

    QString name,surname,email,password,photo;
    name=ui->name->text();
    surname=ui->surname->text();
    email=ui->email->text();
    password=ui->password->text();

    if (filePath.length()==0){
        photo="/img/default-user.png";
    }
    else{
    photo=filePath;
    }
    if(name.length()==0 || surname.length()==0 || email.length()==0){
        ui->status->setText("Complete all the fields!");
    }
    else{
    User user(email,name,surname,password,photo);
    ui->status->setText(QString::number(user.getID()));

    if(user.signup()){
        ui->status->setText("Success");
        if(user.sendEmail(user.getEmail(),user.getName(),user.getSurname())){
            ui->status->setText("Email sent!");
        }
    };

    }


}

void Register::on_pushButton_clicked()
{




}


void Register::on_upload_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(

                    this,

                    tr("Open File"),

                    "",

                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )

                    );



        imageObject = new QImage();

        imageObject->load(imagePath);

        QPixmap profile(imagePath);
        filePath=imagePath;





        ui->photo->setPixmap(profile);
        ui->photo->setScaledContents(true);

}
