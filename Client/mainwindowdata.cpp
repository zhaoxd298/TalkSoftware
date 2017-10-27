#include "MainWindow.h"


void MainWindow::onMinisizeBtn()
{
    this->showMinimized();
}

void MainWindow::onCloseBtn()
{
    //saveUserInfo();
    this->close();
    delete(this);
}


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger :
        setWindowState(Qt::WindowActive);
        activateWindow();
        break;
    default:
        break;
    }
}

// 鼠标支持
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressFlag) {
        QPoint pos = event->globalPos();
        move(this->pos() + pos - m_lastPos);
        m_lastPos = pos;
    }

    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = true;
        m_lastPos = event->globalPos();
    }

    event->ignore();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = false;
    }

    event->ignore();
}
