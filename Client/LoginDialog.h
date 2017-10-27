#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QPaintEvent>
#include <QString>
#include <QList>
#include <QImage>

#include "Socket.h"

struct UserInfo {
    QString id;
    QString passwd;
    bool remeberPasswd;
    bool autoLogin;
};

class LoginDialog : public QWidget
{
    Q_OBJECT
private:
    bool m_pressFlag;
    QPoint m_lastPos;

    QImage m_backImg;
    QImage m_headImg;

    UserInfo curUserInfo;
    QList<UserInfo> userInfos;

    Socket* m_socket;

    QLabel* m_headLogo;
    QLabel* m_backImgLabel;
    QComboBox* m_idCbx;
    QLineEdit* m_passwdEdit;
    QCheckBox* m_remeberPasswd;
    QCheckBox* m_autoLogin;
    QPushButton* m_minisizeBtn;
    QPushButton* m_closeBtn;
    QPushButton* m_loginBtn;
    QPushButton* m_registerAccountBtn;
    QPushButton* m_foundPasswdBtn;

private:
    void constructUI();
    void connectSlots();

    bool saveUserInfo();
    bool loadUserInfo();

private slots:
    void onRegisterCount();
    void onFoundPasswd();
    void onRemeberPasswdChecked(int s);
    void onAutoLoginChecked(int s);
    void onLoginBtn();
    void onIdCurrentTextChanged(const QString &text);
    void onMinisizeBtn();
    void onCloseBtn();


protected:
    void paintEvent(QPaintEvent *);

    // 鼠标支持
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

};

#endif // LOGINDIALOG_H
