#include "TcpServer.h"

#include <QDebug>

TcpServer::TcpServer(QObject *parent, int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any, port);
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    TcpSocket *tcpSocket = new TcpSocket(this);
    connect(tcpSocket, SIGNAL(receivedMsg(QString,int)), this, SLOT(slotReceivedMsg(QString,int)));
    connect(tcpSocket, SIGNAL(disconnected(int)), this, SLOT(slotDisconnected(int)));

    tcpSocket->setSocketDescriptor(socketDescriptor);

    tcpSocketList.append(tcpSocket);

    qDebug() << "Connected by IP:" << tcpSocket->localAddress().toString();
}

void TcpServer::slotReceivedMsg(QString msg, int length)
{
    qDebug() << msg;
    /*emit updateServer(msg,length);
    for(int i=0;i<tcpSocketList.count();i++)
    {
        QTcpSocket *item = tcpSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }*/
}

void TcpServer::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpSocketList.count();i++)
    {
        QTcpSocket *item = tcpSocketList.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            tcpSocketList.removeAt(i);
            return;
        }
    }
    return;
}
