#include "Group.h"

#include <QDebug>

Group::Group(int id, QString name)
{
    m_isHide = true;
    m_id = id;
    m_name = name;
}

Group::~Group()
{
    qDebug() << "Group::~Group()";
    for (int i=0; i<m_friendList.count(); i++) {
        delete m_friendList[i];
    }

    m_friendList.clear();
}

int Group::id()
{
    return m_id;
}

QString Group::name()
{
    return m_name;
}

void Group::addBuddy(Buddy* buddy)
{
    if (NULL == buddy) {
        return;
    }

    m_friendList.append(buddy);
}


void Group::setListwidgetItem(QListWidgetItem* item)
{
    if (NULL != item) {
        m_item = item;
    }
}

void Group::displayGroup(QListWidget* listWidget)
{
    for (int i=0; i<m_friendList.count(); i++) {
        QListWidgetItem *newItem = new QListWidgetItem(listWidget);       //创建一个newItem
        newItem->setSizeHint(QSize(listWidget->width(), 50)); //设置宽度、高度
        listWidget->addItem(newItem);
        listWidget->setItemWidget(newItem, m_friendList[i]);
        newItem->setHidden(m_isHide);
        m_friendList[i]->setListwidgetItem(newItem);
    }
}

QListWidgetItem* Group::item()
{
    return m_item;
}

void Group::mousePress()
{
    //qDebug() << "void Group::mousePress()";

    if (m_isHide) {
        m_item->setIcon(QIcon("://img/openIcon.png"));
    } else {
        m_item->setIcon(QIcon("://img/hideIcon.png"));
    }
    m_isHide = !m_isHide;

    for (int i=0; i<m_friendList.count(); i++) {
        m_friendList[i]->item()->setHidden(m_isHide);
    }
}
