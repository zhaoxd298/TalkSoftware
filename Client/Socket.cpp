#include "Socket.h"


Socket* Socket::c_instance = NULL;

Socket::Socket()
{
    m_connectStatus = false;
    m_runFlag = false;
    m_port = 9999;
    m_ip = "192.168.0.65";
}

Socket::~Socket()
{
    delete m_serverIP;
    delete m_tcpSocket;
    stopThread();
}

bool Socket::construct()
{
    m_serverIP = new QHostAddress();
    m_tcpSocket = new QTcpSocket();

    if (!(m_serverIP && m_tcpSocket)) {
        return false;
    }

    if (!m_serverIP->setAddress(m_ip)) {
        return false;
    }

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));

    m_tcpSocket->connectToHost(*m_serverIP, m_port);

    return true;
}

Socket* Socket::GetInstance()
{
    if (c_instance == NULL) {
        c_instance = new Socket();
        // 若第二阶段构造失败，返回 NULL
        if (!(c_instance && c_instance->construct())) {
            delete c_instance;
            c_instance = NULL;
        }
    }

    return c_instance;
}

bool Socket::connectStatus()
{
    return m_connectStatus;
}

bool Socket::runFlag()
{
    return m_runFlag;
}

void Socket::startThread()
{
    m_runFlag = true;
    //start();
}
void Socket::stopThread()
{
    m_runFlag = false;
    //wait(100000);   // 等待100ms，若线程还不退出，函数返回
}

bool Socket::sendMsg(const char* buf, int size)
{
    if (NULL==buf || size<=0) {
        return false;
    }

    int ret = m_tcpSocket->write(buf, size);
    if (ret != size) {
        return false;
    }

    return true;
}

bool Socket::sendMsg(QString msg)
{
    return sendMsg(msg.toLocal8Bit(), msg.toLocal8Bit().size());
}

bool Socket::userLogin(QString id, QString passwd)
{
    if (!m_connectStatus) {
        //return false;
    }

    return true;
}

bool Socket::registerAccount()
{
    if (!m_connectStatus) {
        //return false;
    }

    return true;
}

bool Socket::foundPasswd()
{
    if (!m_connectStatus) {
        //return false;
    }

    return true;
}

/*
* 1.检查是否连接上服务器，若没有连接服务器
* 2.定期发送心跳包
*/
void Socket::run()
{
    while (m_runFlag); {
        QThread::sleep(1);
    }
}

void Socket::onConnected()
{
    m_connectStatus = true;
}

void Socket::onDisconnected()
{
    m_connectStatus = false;
}

void Socket::onDataReceived()
{

}
