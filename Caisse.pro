#-------------------------------------------------
#
# Project created by QtCreator 2018-10-23T22:26:31
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Caisse
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += SMTP_BUILD

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    pos.cpp \
    connection.cpp \
    caisse.cpp \
    terminal.cpp \
    functions.cpp \
    user.cpp \
    reset.cpp \
    register.cpp \
    session.cpp \
    order.cpp \
    orderdetail.cpp \
    payment.cpp \
    cash.cpp \
    client.cpp \
    QRoundProgressBar.cpp \
    productform.cpp \
    ProgressCircle.cpp \

    functions.cpp \

    mainwindow.cpp \





HEADERS += \
    pos.h \
    connection.h \
    caisse.h \
    terminal.h \
    caisse.h \
    functions.h \
    user.h \
    reset.h \
    register.h \
    session.h \
    order.h \
    orderdetail.h \
    payment.h \
    cash.h \
    client.h \
    QRoundProgressBar.h \
    productform.h \
    ProgressCircle.h \



    mainwindow.h \







FORMS += \
    pos.ui \
    caisse1.ui \
    reset.ui \
    register.ui \
    productform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SMTP_LIBRARY_LOCATION = C:\Users\Lionel\Desktop\SMTPCLIENT

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

RESOURCES += \
    img.qrc \
    src.qrc \
    smtp.qrc
