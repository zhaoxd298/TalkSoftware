#include "Buddy.h"

#include <QDebug>


Buddy::Buddy(int id, QString nickname, QString signature)
{
    m_talkDialog = NULL;

    m_id = id;
    m_nickname = nickname;
    m_signature = signature;

    m_headLabel = new QLabel(this);
    m_nicknameLabel = new QLabel(this);
    m_signatureLabel = new QLabel(this);

    m_headLabel->setFixedSize(36, 40);
    m_headLabel->setToolTip(QString::number(id));
    m_headLabel->setPixmap(QPixmap("://img/headIcon.jpg").scaled(m_headLabel->width(), m_headLabel->height()));
    m_nicknameLabel->setText(nickname);
    m_signatureLabel->setText(signature);

    //设置个性签名字体为灰色
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    m_signatureLabel->setPalette(color);

    m_vlayout = new QVBoxLayout();
    m_vlayout->addWidget(m_nicknameLabel);
    m_vlayout->addWidget(m_signatureLabel);

    //mainLayout->setSpacing(10);
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(m_headLabel);
    mainLayout->addLayout(m_vlayout);

    setLayout(mainLayout);
}

Buddy::~Buddy()
{
    delete m_talkDialog;
}


int Buddy::id()
{
    return m_id;
}

QString Buddy::nickname()
{
    return m_nickname;
}

QString Buddy::signature()
{
    return m_signature;
}

QImage Buddy::headIcon()
{
    return m_headIcon;
}


QListWidgetItem* Buddy::item()
{
    return m_item;
}

void Buddy::setListwidgetItem(QListWidgetItem* item)
{
    if (NULL != item) {
        m_item = item;
    }
}

void Buddy::mousePressEvent(QMouseEvent *) //鼠标点击事件
{
    //qDebug() << "void Buddy::mousePressEvent(QMouseEvent *event)";
}

void Buddy::mouseDoubleClickEvent(QMouseEvent *)
{
    //qDebug() << "void Buddy::mouseDoubleClickEvent(QMouseEvent *event)";
    if (NULL == m_talkDialog) {
        m_talkDialog = new TalkDialog(this);
        m_talkDialog->setWindowTitle(m_nickname);
    }
    m_talkDialog->show();
}
