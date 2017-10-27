#include "TalkDialog.h"

#include <QDebug>

void TalkDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressFlag) {
        if (m_isMaxsize) {      // 有问题
            m_isMaxsize = false;
            this->showNormal();
            /*resize(m_lastSize);
            setWindowState(Qt::WindowNoState);
            int x = event->pos().x() - m_lastSize.width() / 2;
            if (x < 0) {
                x = 0;
            }
            this->move(x, event->pos().y());
            m_maxisizeBtn->setStyleSheet(m_maxsizeBtnStyle);
            */
        } else {
            QPoint pos = event->globalPos();
            move(this->pos() + pos - m_lastPos);
            m_lastPos = pos;
        }
    }

    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void TalkDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->pos().y() < 100) {
        onMaxsizeBtn();
    }

    event->ignore();
}

void TalkDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = true;
        m_lastPos = event->globalPos();
    }

    event->ignore();
}

void TalkDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = false;
    }

    event->ignore();
}

void TalkDialog::onMinisizeBtn()
{
    this->showMinimized();
}
void TalkDialog::onMaxsizeBtn()
{
    if (!m_isMaxsize) {
        //qDebug() << windowState();
        m_lastSize = this->size();
        this->showMaximized();
        m_maxisizeBtn->setStyleSheet(m_restoreBtnStyle);
    } else {
        this->showNormal();
        m_maxisizeBtn->setStyleSheet(m_maxsizeBtnStyle);
    }
    m_isMaxsize = !m_isMaxsize;
}

void TalkDialog::onCloseBtn()
{
    this->close();
}
void TalkDialog::onSendBtn()
{
    QString msg = m_inputArea->toPlainText();

    if (m_socket) {
        m_socket->sendMsg(msg);
    }

    qDebug() << "msg:" << msg;
}
