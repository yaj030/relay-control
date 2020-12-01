#-------------------------------------------------
#
# Project created by QtCreator 2019-05-18T15:09:00
#
#-------------------------------------------------

QT += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = relay_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    mywidget.cpp \
    qcirindicator.cpp \
    relay.cpp \
    serialportdialog.cpp

HEADERS  += mainwindow.h \
    form.h \
    mywidget.h \
    qcirindicator.h \
    relay.h \
    serialportdialog.h

FORMS    += mainwindow.ui \
    form.ui
