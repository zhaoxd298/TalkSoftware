#ifndef SOCKET_H
#define SOCKET_H


#include <QThread>
#include <QHostAddress>
#include <QTcpSocket>

class Socket : public QThread
{
    Q_OBJECT

private:
    static Socket* c_instance;

    int m_port;
    QString m_ip;
    QHostAddress* m_serverIP;
    QTcpSocket* m_tcpSocket;

    bool m_connectStatus;      // 标识是否连接上服务器
    bool m_runFlag;     // 线程运行标志

private:
    Socket();
    Socket(const Socket&);
    Socket& operator= (const Socket&);
    bool construct();       // 二阶构造

protected:
    void run();     // 线程入口函数

protected slots:
    void onConnected();
    void onDisconnected();
    void onDataReceived();

public:
    static Socket* GetInstance();
    ~Socket();

    bool connectStatus();
    bool runFlag();
    void startThread();
    void stopThread();

    bool sendMsg(const char* buf, int size);
    bool sendMsg(QString msg);
    bool userLogin(QString id, QString passwd);     // 用户登录
    bool registerAccount();     // 注册账号
    bool foundPasswd();         // 找回密码
};

#endif // SOCKET_H
