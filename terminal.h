#ifndef TERMINAL_H
#define TERMINAL_H
#include <iostream>
#include <windows.h>
#include <QDialog>



using namespace std;


class Terminal
{
private:
    int ID;
    QString name;

public:
    Terminal();

    void setID(int ID1);
    int getID();
    void setName(QString name1);
    QString getName();

    bool saveTerminal();
};

#endif // TERMINAL_H
