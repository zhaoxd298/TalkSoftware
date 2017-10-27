#include "MainWindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFont>
#include <QIcon>
#include <QListWidgetItem>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":/img/softwareIcon.png"));

    QSystemTrayIcon *trayIcon= new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/img/softwareIcon.png"));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();

    m_pressFlag = false;

    loadResources();
    constructUI();
    connectSlots();
    initDisplayArea();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
}

void MainWindow::loadResources()
{
    m_mainBackImg.load(":/img/mainBackImg.jpg");
    m_searchImg.load(":/img/search.png");
    m_headImg.load(":/img/head.jpg");
}

void MainWindow::constructUI()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    m_mainBackLabel = new QLabel(this);
    m_mainBackLabel->setFixedHeight(150);

    m_mainLayout.setContentsMargins(0, 0, 0, 0);

    m_mainLayout.addWidget(m_mainBackLabel);
    m_mainLayout.addWidget(&m_displayArea);

    setLayout(&m_mainLayout);

    m_submainLayout = new QVBoxLayout;
    m_submainLayout->setContentsMargins(10, 0, 0, 0);
    m_headLabel.setFixedSize(65, 65);
    m_idLabel.setText("雪狼");
    m_signEdit.setFrame(false);
    m_signEdit.setPlaceholderText("编辑个性签名");
    m_signEdit.setStyleSheet("background-color: rgb(255, 255, 255, 0);");

    m_minisizeBtn = new QPushButton(this);;
    m_closeBtn = new QPushButton(this);;
    m_minisizeBtn->setFixedSize(24, 24);
    QString minisizeBtnStyle = "\
        QPushButton{\
            border-image:url(:/img/minisize.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/minisizeHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/minisizePressed.png);\
        }";
    m_minisizeBtn->setStyleSheet(minisizeBtnStyle);
    m_closeBtn->setFixedSize(24, 24);
    QString closeBtnStyle = "\
        QPushButton{\
            border-image:url(:/img/close.png);\
        }\
        QPushButton:hover{\
            border-image:url(:/img/closeHover.png);\
        }\
        QPushButton:pressed{\
            border-image:url(:/img/closePressed.png);\
        }";
    m_closeBtn->setStyleSheet(closeBtnStyle);
    m_subHLayout0 = new QHBoxLayout;
    m_subHLayout0->setContentsMargins(0, 0, 0, 0);
    m_subHLayout0->setSpacing(0);
    m_subHLayout0->addStretch();
    m_subHLayout0->addWidget(m_minisizeBtn);
    m_subHLayout0->addWidget(m_closeBtn);

    m_subVLayout = new QVBoxLayout;
    m_subVLayout->setSpacing(10);
    m_subVLayout->addWidget(&m_idLabel);
    m_subVLayout->addWidget(&m_signEdit);
    m_subVLayout->addStretch();

    m_subHLayout1 = new QHBoxLayout;
    m_subHLayout1->addWidget(&m_headLabel);
    m_subHLayout1->addLayout(m_subVLayout);

    m_searchLabel.setPixmap(QPixmap::fromImage(m_searchImg));
    m_searchLabel.setFixedSize(24, 30);

    m_searchEdit.setFixedHeight(30);
    m_searchEdit.setFrame(false);
    m_searchEdit.setPlaceholderText("搜索");
    m_searchEdit.setStyleSheet("background-color: rgb(255, 255, 255, 80);");

    m_subHLayout2 = new QHBoxLayout;
    m_subHLayout2->addWidget(&m_searchLabel);
    m_subHLayout2->addWidget(&m_searchEdit);

    m_submainLayout->addLayout(m_subHLayout0);
    m_submainLayout->addStretch();
    m_submainLayout->addLayout(m_subHLayout1);
    m_submainLayout->addLayout(m_subHLayout2);

    m_mainBackLabel->setLayout(m_submainLayout);

    resize(300, 700);
    setMinimumWidth(300);
}

void MainWindow::connectSlots()
{
    connect(m_minisizeBtn, SIGNAL(clicked(bool)), this, SLOT(onMinisizeBtn()));
    connect(m_closeBtn, SIGNAL(clicked(bool)), this, SLOT(onCloseBtn()));
}

void MainWindow::initDisplayArea()
{
    m_displayArea.setTabShape(QTabWidget::Triangular);
    m_displayArea.setDocumentMode(true);
    m_displayArea.setIconSize(QSize(20, 20));
    QString tabBarStyle =
        "QTabWidget::pane{\
            border:none;\
        }\
        QTabWidget::tab-bar{\
                alignment:left;\
        }\
        QTabBar::tab{\
            background:transparent;\
            color:white;\
            min-width:30ex;\
            min-height:10ex;\
        }\
        QTabBar::tab:hover{\
            background:rgb(255, 151, 68, 100);\
        }\
        QTabBar::tab:selected{\
            border-color:rgb(111, 151, 68, 100);\
            background:rgb(111, 151, 68, 80);\
            color:green;\
        }";
    m_displayArea.setStyleSheet(tabBarStyle);

    dialogListWidget = new QListWidget;
    dialogListWidget->setFrameStyle(0);

    friendList = new FriendList(this);
    friendList->setFrameStyle(0);

    groupChatListWidget = new QListWidget;
    groupChatListWidget->setFrameStyle(0);

    m_displayArea.addTab(dialogListWidget, QIcon(QPixmap(":/img/dialogIcon.png")), "");
    m_displayArea.addTab(friendList, QIcon(QPixmap(":/img/friendListIcon.png")), "");
    m_displayArea.addTab(groupChatListWidget, QIcon(QPixmap(":/img/groupChatIcon.png")), "");

    m_displayArea.setTabToolTip(0, "会话");
    m_displayArea.setTabToolTip(1, "联系人");
    m_displayArea.setTabToolTip(2, "群聊");

    m_displayArea.setCurrentIndex(1);
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(m_mainBackLabel->x(), m_mainBackLabel->y(), m_mainBackLabel->width(),
            m_mainBackLabel->height(), QPixmap::fromImage(m_mainBackImg));

    painter.setRenderHint(QPainter::Antialiasing, true);    // 让图像边缘显示平滑
    QPainterPath path;
    path.addEllipse(m_headLabel.x(), m_headLabel.y(),
                    m_headLabel.width(), m_headLabel.height());
    painter.setClipPath(path);

    painter.drawPixmap(m_headLabel.x(), m_headLabel.y(), m_headLabel.width(),
                       m_headLabel.height(), QPixmap::fromImage(m_headImg));
    painter.setRenderHint(QPainter::Antialiasing, false);
}



