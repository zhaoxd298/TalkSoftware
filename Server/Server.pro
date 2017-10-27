#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T16:44:17
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TcpSocket.cpp \
    TcpServer.cpp

HEADERS  += mainwindow.h \
    TcpSocket.h \
    TcpServer.h
