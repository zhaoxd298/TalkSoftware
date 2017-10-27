#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T21:26:03
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalkClient
TEMPLATE = app


SOURCES += main.cpp\
        LoginDialog.cpp \
    MainWindowUI.cpp \
    MainWindowData.cpp \
    FriendList.cpp \
    Buddy.cpp \
    Group.cpp \
    TalkDialogUI.cpp \
    TalkDialogData.cpp \
    Socket.cpp \
    Message.cpp

HEADERS  += LoginDialog.h \
    MainWindow.h \
    FriendList.h \
    Buddy.h \
    Group.h \
    TalkDialog.h \
    Socket.h \
    Message.h

RESOURCES += \
    resources.qrc
