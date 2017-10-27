#include "TcpSocket.h"

TcpSocket::TcpSocket(QObject *)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

void TcpSocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        //char buf[1024];
        //read(buf, length);

        QByteArray array = read(length);

        QString msg = QString::fromLocal8Bit(array);
        emit receivedMsg(msg, length);
    }
}

void TcpSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
