#ifndef MESSAGE_H
#define MESSAGE_H

#include "Socket.h"

#pragma pack(push, 1)
/*数据包结构，一个数据包固定采用1024 byte*/
struct MsgData {
    unsigned short len;         // 有效数据长度
    unsigned char code;         // 指令代码
    unsigned char param;        // 指令参数
    unsigned char packageType;  // 数据包类型
    unsigned char dataAddr;     // 数据开始的偏移地址
    char buf[1018];             // 数据缓存
    unsigned char sum;          // 整个数据包的校验和，不包括自己
};
#pragma pack(pop)

class Message
{
private:
    MsgData m_msgData;
    Socket* m_socket;
public:
    Message(unsigned char code, unsigned char param, QString data="");
};

#endif // MESSAGE_H
