#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "TcpSocket.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent=0, int port=0);
    QList<TcpSocket*> tcpSocketList;
signals:
    void updateServer(QString, int);
public slots:
    void slotReceivedMsg(QString,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
