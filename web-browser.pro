#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T14:00:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = web-browser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webbroswerwindow.cpp \
    webbrowserapp.cpp

HEADERS  += mainwindow.h \
    webbroswerwindow.h \
    webbrowserapp.h

FORMS    += mainwindow.ui
