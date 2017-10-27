#include "LoginDialog.h"
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QToolTip>
#include <QFile>
#include <QDataStream>
#include <MainWindow.h>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent)
    : QWidget(parent)
{
    m_pressFlag = false;

    setWindowIcon(QIcon(":/img/softwareIcon0.png"));

    constructUI();
    connectSlots();

    loadUserInfo();

    m_socket = Socket::GetInstance();

    m_backImg.load(":/img/backImg.JPG");
    m_headImg.load(":/img/head.jpg");
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::constructUI()
{
    m_headLogo = new QLabel(this);
    m_backImgLabel = new QLabel(this);
    m_idCbx = new QComboBox(this);
    m_passwdEdit = new QLineEdit(this);
    m_remeberPasswd = new QCheckBox(this);
    m_autoLogin = new QCheckBox(this);
    m_minisizeBtn = new QPushButton(this);;
    m_closeBtn = new QPushButton(this);;
    m_loginBtn = new QPushButton(this);
    m_registerAccountBtn = new QPushButton(this);
    m_foundPasswdBtn = new QPushButton(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //setStyleSheet("border-radius:5px");

    resize(420, 300);
    setFixedSize(width(), height());

    m_backImgLabel->resize(width(), 140);
    m_backImgLabel->move(0, 0);

    m_minisizeBtn->setFixedSize(24, 24);
    m_minisizeBtn->move(this->width()-48, 0);
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
    m_closeBtn->move(this->width()-24, 0);
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

    m_headLogo->resize(90, 90);
    m_headLogo->move(10, 150);

    m_idCbx->setEditable(true);
    m_idCbx->resize(200, 30);
    m_idCbx->move(110, 150);

    m_registerAccountBtn->resize(80, 30);
    m_registerAccountBtn->move(320, 150);
    m_registerAccountBtn->setText("注册账号");
    QString btnStyle1 = "\
        QPushButton{\
            color: rgb(38, 133, 227);\
            border:1px;\
        }\
        QPushButton:hover{\
            color: rgb(97, 179, 246);\
        }\
        QPushButton:pressed{\
            color: rgb(38, 133, 227);\
        }";
    m_registerAccountBtn->setStyleSheet(btnStyle1);


    m_passwdEdit->setEchoMode(QLineEdit::Password);
    m_passwdEdit->resize(200, 30);
    m_passwdEdit->move(110, 190);

    m_foundPasswdBtn->setText("找回密码");
    m_foundPasswdBtn->resize(80, 30);
    m_foundPasswdBtn->move(320, 190);
    m_foundPasswdBtn->setStyleSheet(btnStyle1);

    m_remeberPasswd->setText("记住密码");
    m_remeberPasswd->move(110, 230);

    m_autoLogin->setText("自动登录");
    m_autoLogin->move(245, 230);

    m_loginBtn->setText("登录");
    m_loginBtn->resize(200, 30);
    m_loginBtn->move(110, 260);
    QString btnStyle2 =
        "QPushButton{\
            color: rgb(255, 255, 255);\
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(166,164,208), stop:0.3 rgb(171,152,230), stop:1 rgb(152,140,220));\
            border:1px;\
            border-radius:5px; /*border-radius控制圆角大小*/\
            padding:2px 4px;  \
        }\
        QPushButton:hover{\
            color: rgb(255, 255, 255); \
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(130,120,226), stop:0.3 rgb(120,130,230), stop:1 rgb(125,140,226));\
            border:1px;  \
            border-radius:5px; /*border-radius控制圆角大小*/\
            padding:2px 4px; \
        }\
        QPushButton:pressed{    \
            color: rgb(255, 255, 255); \
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240,156,121), stop:0.3 rgb(220,160,140), stop:1 rgb(230,140,120));  \
            border:1px;  \
            border-radius:5px; /*border-radius控制圆角大小*/\
            padding:2px 4px; \
        }";
    m_loginBtn->setStyleSheet(btnStyle2);
}


void LoginDialog::connectSlots()
{
    connect(m_registerAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onRegisterCount()));
    connect(m_foundPasswdBtn, SIGNAL(clicked(bool)), this, SLOT(onFoundPasswd()));
    connect(m_remeberPasswd, SIGNAL(stateChanged(int)), this, SLOT(onRemeberPasswdChecked(int)));
    connect(m_autoLogin, SIGNAL(stateChanged(int)), this, SLOT(onAutoLoginChecked(int)));
    connect(m_loginBtn, SIGNAL(clicked(bool)), this, SLOT(onLoginBtn()));
    connect(m_idCbx, SIGNAL(currentTextChanged(QString)), this, SLOT(onIdCurrentTextChanged(const QString)));
    connect(m_minisizeBtn, SIGNAL(clicked(bool)), this, SLOT(onMinisizeBtn()));
    connect(m_closeBtn, SIGNAL(clicked(bool)), this, SLOT(onCloseBtn()));
}





bool LoginDialog::saveUserInfo()
{
    bool flag = false;

    for (int i=0; i<userInfos.count(); i++) {
        //qDebug() << curUserInfo.id << ":" << userInfos[i].id;
        if (curUserInfo.id == userInfos[i].id) {
            flag = true;
            userInfos[i] = curUserInfo;
            break;
        }
    }

    if (false == flag) {
        userInfos.insert(0, curUserInfo);
        //qDebug() << "userInfos.insert(0, curUserInfo);";
    }

    QFile file("e:/TalkInfo.txt");
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);

    for (int i =0; i<userInfos.count(); i++) {
        out << userInfos[i].id;
        out << userInfos[i].passwd;
        out << userInfos[i].remeberPasswd;
        out << userInfos[i].autoLogin;
    }

    file.close();

    return true;
}

bool LoginDialog::loadUserInfo()
{
    QFile file("e:/TalkInfo.txt");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    int i = 0;
    while (!in.atEnd()) {
        in >> curUserInfo.id;
        in >> curUserInfo.passwd;
        in >> curUserInfo.remeberPasswd;
        in >> curUserInfo.autoLogin;

        //qDebug() << "id:" << curUserInfo.id;
        //qDebug() << "passwd:" << curUserInfo.passwd;
        //qDebug() << "remeberPasswd:" << curUserInfo.remeberPasswd;
        //qDebug() << "autoLogin:" << curUserInfo.autoLogin << endl;


        m_idCbx->addItem(curUserInfo.id);

        if (0 == i) {
            if (true==curUserInfo.remeberPasswd) {
                m_passwdEdit->setText(curUserInfo.passwd);
            }

            m_remeberPasswd->setChecked(curUserInfo.remeberPasswd);
            m_autoLogin->setChecked(curUserInfo.autoLogin);
        }

        userInfos.append(curUserInfo);
        i++;
    }

    file.close();

    return true;
}


void LoginDialog::onRegisterCount()
{
    if (NULL != m_socket) {
        m_socket->registerAccount();
    }
}


void LoginDialog::onFoundPasswd()
{
    if (NULL != m_socket) {
        m_socket->foundPasswd();
    }
}

void LoginDialog::onRemeberPasswdChecked(int s)
{
    if (0 == s) {
        curUserInfo.remeberPasswd = false;
        m_passwdEdit->clear();
    } else {
        curUserInfo.remeberPasswd = true;
    }

    //saveUserInfo();
}

void LoginDialog::onAutoLoginChecked(int s)
{
    if (0 == s) {
        curUserInfo.autoLogin = false;
    } else {
        curUserInfo.autoLogin = true;
    }

    //saveUserInfo();
}

void LoginDialog::onLoginBtn()
{
    curUserInfo.id = m_idCbx->lineEdit()->text();
    curUserInfo.passwd = m_passwdEdit->text();
    curUserInfo.remeberPasswd = m_remeberPasswd->isChecked();
    curUserInfo.autoLogin = m_autoLogin->isChecked();

    if (curUserInfo.id == "") {
        //QToolTip tip;
        QToolTip::showText(QPoint(x()+m_idCbx->x(), y()+m_idCbx->y()), "请您输入账号后再登录");
        return;
    }

    if (curUserInfo.passwd == "") {
        //QToolTip tip;
        QToolTip::showText(QPoint(x()+m_passwdEdit->x(), y()+m_passwdEdit->y()), "请您输入密码后再登录");
        return;
    }

    /*qDebug() << endl;
    qDebug() << "void LoginDialog::onLoginBtn()";
    qDebug() << "id:" << curUserInfo.id;
    qDebug() << "passwd:" << curUserInfo.passwd;
    qDebug() << "remeberPasswd:" << curUserInfo.remeberPasswd;
    qDebug() << "autoLogin:" << curUserInfo.autoLogin;
    */


    // 向服务器验证账号、密码
    if (NULL != m_socket) {
        if (!m_socket->userLogin(curUserInfo.id, curUserInfo.passwd)) {
            // 弹出密码错误
            return;
        }
    }
    // 启动新的界面
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    //mainWindow->activateWindow();

    // 关闭当前界面
    this->close();
    //this->hide();
    saveUserInfo();
}


void LoginDialog::onIdCurrentTextChanged(const QString &text)
{
    //qDebug() << text;
    bool flag = false;
    UserInfo userInfo;
    for (int i=0; i<userInfos.count(); i++) {
        if (text == userInfos[i].id) {
            flag = true;
            userInfo = userInfos[i];
            userInfos.removeAt(i);
            userInfos.insert(0, userInfo);
            break;
        }
    }

    m_passwdEdit->clear();
    m_remeberPasswd->setChecked(false);
    m_autoLogin->setChecked(false);

    if (flag) {
        if (true==userInfo.remeberPasswd) {
            m_passwdEdit->setText(userInfo.passwd);
        }

        m_remeberPasswd->setChecked(userInfo.remeberPasswd);
        m_autoLogin->setChecked(userInfo.autoLogin);
    }
}

void LoginDialog::onMinisizeBtn()
{
    this->showMinimized();
}

void LoginDialog::onCloseBtn()
{
    saveUserInfo();
    this->close();
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(m_backImgLabel->x(), m_backImgLabel->y(), m_backImgLabel->width(),
        m_backImgLabel->height(), QPixmap::fromImage(m_backImg));


    painter.setRenderHint(QPainter::Antialiasing, true);    // 让图像边缘显示平滑
    QPainterPath path;
    path.addEllipse(m_headLogo->x(), m_headLogo->y(),
                    m_headLogo->width(), m_headLogo->height());

    painter.setClipPath(path);

    painter.drawPixmap(m_headLogo->x(), m_headLogo->y(), m_headLogo->width(),
        m_headLogo->height(), QPixmap::fromImage(m_headImg));
    painter.setRenderHint(QPainter::Antialiasing, false);
}


void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressFlag) {
        QPoint pos = event->globalPos();
        move(this->pos() + pos - m_lastPos);
        m_lastPos = pos;
    }

    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}


void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = true;
        m_lastPos = event->globalPos();
    }

    event->ignore();
}


void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressFlag = false;
    }

    event->ignore();
}



