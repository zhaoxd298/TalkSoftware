#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QMouseEvent>
#include <QList>
#include <QHBoxLayout>

#include "Buddy.h"
#include "Group.h"


class FriendList : public QListWidget
{
    Q_OBJECT
private:
    QWidget* m_parent;
    QList<Group*> m_groupList;    // 分组列表


protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    explicit FriendList(QWidget *parent);
    ~FriendList();

    void addGroup(Group* group);

    bool getFriendList();       // 获取好友列表
    void displayFriendList();   // 将好友列表显示到界面
    void mousePree(QMouseEvent *event);
};

#endif // FRIENDLIST_H
