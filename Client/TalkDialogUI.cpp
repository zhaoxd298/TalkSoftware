#include "TalkDialog.h"
#include <QPalette>
#include <QPainter>
#include <QPixmap>

#include "Buddy.h"

#include <QDebug>

TalkDialog::TalkDialog(Buddy *parent) : m_buddy(parent)
{
    m_pressFlag = false;
    m_isMaxsize = false;

    m_socket = Socket::GetInstance();

    loadResource();
    constructUI();
    connectSlots();
}


TalkDialog::~TalkDialog()
{
    qDebug() << "TalkDialog::~TalkDialog()";
}


void TalkDialog::loadResource()
{
    m_backgroudImg.load(":/img/talkDialogBackgroud2.jpg");
    m_headImg.load(":/img/head.jpg");

    m_maxsizeBtnStyle = "\
        QPushButton{\
            border-image:url(://img/maxsizeIcon.png);\
        }\
        QPushButton:hover{\
            border-image:url(://img/maxsizeHoverIcon.png);\
        }\
        QPushButton:pressed{\
            border-image:url(://img/maxsizePressedIcon.png);\
        }";
    m_restoreBtnStyle = "\
        QPushButton{\
            border-image:url(://img/restoreIcon.png);\
        }\
        QPushButton:hover{\
            border-image:url(://img/restoreHoverIcon.png);\
        }\
        QPushButton:pressed{\
            border-image:url(://img/restorePressedIcon.png);\
        }";
}

void TalkDialog::constructUI()
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setMinimumSize(600, 500);

    m_headLabel = new QLabel(this);
    m_headLabel->setFixedSize(32, 32);

    m_nicknameLabel = new QLabel(this);
    m_nicknameLabel->setText(m_buddy->nickname());

    m_minisizeBtn = new QPushButton(this);
    m_minisizeBtn->setFixedSize(24, 24);
    m_minisizeBtn->move(width()-72, 0);
    QString minisizeBtnStyle = "\
        QPushButton{\
            border-image:url(:/img/talkDigMinisize.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/talkDigMinisizeHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/talkDigMinisizePressed.png);\
        }";
    m_minisizeBtn->setStyleSheet(minisizeBtnStyle);

    m_maxisizeBtn = new QPushButton(this);
    m_maxisizeBtn->setFixedSize(24, 24);
    m_maxisizeBtn->move(width()-48, 0);
    m_maxisizeBtn->setStyleSheet(m_maxsizeBtnStyle);

    m_closeBtn0 = new QPushButton(this);
    m_closeBtn0->setFixedSize(24, 24);
    m_closeBtn0->move(width()-24, 0);
    QString closeBtn0Style = "\
        QPushButton{\
            border-image:url(:/img/talkDigClose.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/talkDigCloseHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/talkDigClosePressed.png);\
        }";
    m_closeBtn0->setStyleSheet(closeBtn0Style);

    m_msgDisplayArea = new QPlainTextEdit(this);
    m_msgDisplayArea->setFrameStyle(0);
    m_msgDisplayArea->setReadOnly(true);

    m_inputArea = new QPlainTextEdit(this);
    m_inputArea->setMaximumHeight(100);
    m_closeBtn1 = new QPushButton(this);
    m_closeBtn1->setText("关闭");
    m_sendBtn = new QPushButton(this);
    m_sendBtn->setText("发送");

    m_hlayout1 = new QHBoxLayout;
    m_hlayout2 = new QHBoxLayout;
    m_mainLayout = new QVBoxLayout(this);

    m_hlayout1->setContentsMargins(10, 10, 0, 20);
    m_hlayout1->addWidget(m_headLabel);
    m_hlayout1->addWidget(m_nicknameLabel);
    m_hlayout1->addStretch();

    m_hlayout2->addStretch();
    m_hlayout2->addWidget(m_closeBtn1);
    m_hlayout2->addWidget(m_sendBtn);

    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_mainLayout->addLayout(m_hlayout1);
    m_mainLayout->addWidget(m_msgDisplayArea);
    m_mainLayout->addWidget(m_inputArea);
    m_mainLayout->addLayout(m_hlayout2);
}

void TalkDialog::connectSlots()
{
    connect(m_minisizeBtn, SIGNAL(clicked(bool)), this, SLOT(onMinisizeBtn()));
    connect(m_maxisizeBtn, SIGNAL(clicked(bool)), this, SLOT(onMaxsizeBtn()));
    connect(m_closeBtn0, SIGNAL(clicked(bool)), this, SLOT(onCloseBtn()));
    connect(m_closeBtn1, SIGNAL(clicked(bool)), this, SLOT(onCloseBtn()));
    connect(m_sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtn()));
}

void TalkDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, width(), height(), QPixmap::fromImage(m_backgroudImg));

    painter.setRenderHint(QPainter::Antialiasing, true);    // 让图像边缘显示平滑
    QPainterPath path;
    path.addEllipse(m_headLabel->x(), m_headLabel->y(),
                    m_headLabel->width(), m_headLabel->height());

    painter.setClipPath(path);

    painter.drawPixmap(m_headLabel->x(), m_headLabel->y(), m_headLabel->width(),
        m_headLabel->height(), QPixmap::fromImage(m_headImg));
    painter.setRenderHint(QPainter::Antialiasing, false);
}


void TalkDialog::resizeEvent(QResizeEvent *event)
{
    m_minisizeBtn->move(width()-72, 0);
    m_maxisizeBtn->move(width()-48, 0);
    m_closeBtn0->move(width()-24, 0);

    event->ignore();
}





