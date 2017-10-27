#include "LoginDialog.h"
#include <QApplication>

#include "Message.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   //qDebug() << sizeof(Message);

    LoginDialog w;
    w.show();

    return a.exec();
}
