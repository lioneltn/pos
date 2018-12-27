#include "caisse.h"
#include <QApplication>
#include <QMessageBox>
#include "caisse.cpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Caisse w;
    w.show();



    return a.exec();
}
