QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE     = app
QT          += network
SOURCES	     = main.cpp \
               MyClient.cpp \
               maketras.cpp \
               mkclientsocket.cpp
HEADERS      = MyClient.h \
    convcoor.h \
    maketras.h \
    mkclientsocket.h
win32:TARGET = ../MyClient

