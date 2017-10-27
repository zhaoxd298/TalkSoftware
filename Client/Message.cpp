#include <stdlib.h>
#include "Message.h"

Message::Message(unsigned char code, unsigned char param, QString data)
{
    memset(&m_msgData, 0, sizeof(MsgData));

    m_msgData.code = code;
    m_msgData.param = param;

    int size = (data.size() > static_cast<int>(sizeof(m_msgData.buf))) ? sizeof(m_msgData.buf) : data.size();

    memcpy(m_msgData.buf, data.toLatin1().data(), size);
}
