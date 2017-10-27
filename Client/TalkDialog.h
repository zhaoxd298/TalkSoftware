#ifndef TALKDIALOG_H
#define TALKDIALOG_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QImage>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>
#include <QMenu>

#include "Socket.h"

//#include <Buddy.h>
class Buddy;

class TalkDialog : public QWidget
{
    Q_OBJECT
private:
    bool m_pressFlag;
    bool m_isMaxsize;
    QPoint m_lastPos;
    QSize m_lastSize;

    QString m_maxsizeBtnStyle;
    QString m_restoreBtnStyle;

    QImage m_backgroudImg;
    QImage m_headImg;

    QLabel* m_headLabel;
    QLabel* m_nicknameLabel;
    QPlainTextEdit* m_msgDisplayArea;
    QPlainTextEdit* m_inputArea;
    QPushButton* m_minisizeBtn;
    QPushButton* m_maxisizeBtn;
    QPushButton* m_closeBtn0;
    QPushButton* m_closeBtn1;
    QPushButton* m_sendBtn;

    QHBoxLayout* m_hlayout0;
    QHBoxLayout* m_hlayout1;
    QHBoxLayout* m_hlayout2;
    QVBoxLayout* m_mainLayout;

    Buddy* m_buddy;

    Socket* m_socket;

    void loadResource();
    void constructUI();
    void connectSlots();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    explicit TalkDialog(Buddy *parent = 0);
    virtual ~TalkDialog();

public slots:
    void onMinisizeBtn();
    void onMaxsizeBtn();
    void onCloseBtn();
    void onSendBtn();
};

#endif // TALKDIALOG_H
