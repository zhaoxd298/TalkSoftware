#include "FriendList.h"
#include <QLabel>
#include <QPixmap>
#include "Buddy.h"

#include <QDebug>


FriendList::FriendList(QWidget *parent) : QListWidget(parent), m_parent(parent)
{
    getFriendList();
    displayFriendList();
}

FriendList::~FriendList()
{
    qDebug() << "FriendList::~FriendList()";
    for (int i=0; i<m_groupList.count(); i++) {
        delete m_groupList[i];
    }

    m_groupList.clear();
}


void FriendList::addGroup(Group *group)
{
    if (NULL == group) {
        return;
    }

    m_groupList.append(group);
}


bool FriendList::getFriendList()       // 获取好友列表
{
    return true;
}



void FriendList::displayFriendList()   // 将好友列表显示到界面
{
    Group* group = new Group(0, "Family");
    Buddy* buddy0 = new Buddy(0, "珊珊", "It's a good day!");
    Buddy* buddy1 = new Buddy(1, "小芳", "啦啦啦");
    group->addBuddy(buddy0);
    group->addBuddy(buddy1);
    addGroup(group);

    Group* group1 = new Group(1, "Friends");
    Buddy* buddy2 = new Buddy(2, "路人甲");
    group1->addBuddy(buddy2);
    addGroup(group1);

    for (int i=0; i<m_groupList.count(); i++) {
        QIcon hideIcon("://img/hideIcon.png");
        QListWidgetItem *newItem = new QListWidgetItem(hideIcon, m_groupList[i]->name());       //创建一个newItem
        newItem->setSizeHint(QSize(m_parent->width(), 32)); //设置宽度、高度
        addItem(newItem);
        newItem->setHidden(false);
        m_groupList[i]->setListwidgetItem(newItem);
        m_groupList[i]->displayGroup(this);
    }
}


void FriendList::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mousePressEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);

    mousePree(event);
}


void FriendList::mouseDoubleClickEvent(QMouseEvent *event)
{
    //qDebug() << "void FriendList::mouseDoubleClickEvent(QMouseEvent *event)";
    QListWidget::mousePressEvent(event);

    mousePree(event);
}

void FriendList::mousePree(QMouseEvent *event)
{
    QListWidgetItem *currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取

    if (event->button()==Qt::LeftButton && currentItem!=NULL) {
        for (int i=0; i<m_groupList.count(); i++) {
            if (currentItem == m_groupList[i]->item()) {
                m_groupList[i]->mousePress();
            }
        }
    }
}
