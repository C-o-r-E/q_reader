#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T15:47:35
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 5)

TARGET = q_reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

linux-g++ {
 LIBS += -lnfc
}

macx: LIBS += -L$$PWD/../../../local_install/lib/ -lnfc.5

INCLUDEPATH += $$PWD/../../../local_install/include
DEPENDPATH += $$PWD/../../../local_install/include
