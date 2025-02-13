#ifndef USERREGISTERWIDGET_H
#define USERREGISTERWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QProcess>
#include <QKeyEvent>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

#include "local_lineedit.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <dbt.h>
#include <devguid.h>
#endif

//using QtJson::JsonObject;
//using QtJson::JsonArray;

namespace Ui {
class UserRegisterWidget;
}

class UserRegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserRegisterWidget(QWidget *parent = nullptr);
    ~UserRegisterWidget();

private slots:
    void slot_username_linedit_focussed(bool);//用户名输入框获取或失去鼠标焦点出发的槽函数
    void slot_password1_linedit_focussed(bool);//口令1输入框获取或失去鼠标焦点出发的槽函数
    void slot_password2_linedit_focussed(bool);//口令2输入框获取或失去鼠标焦点出发的槽函数

    void on_register_pushButton_clicked();

    void slot_username_textChanged(QString);

    void slot_password1_textChanged(QString);

    void slot_password2_textChanged(QString);


private slots:
    void slot_replyFinished(QNetworkReply* reply);
    void slot_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void slot_provideAuthenication(QNetworkReply* reply, QAuthenticator* authenticator);
    void slot_NetWorkError(QNetworkReply::NetworkError);

    void on_close_pushButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);

private:
    Ui::UserRegisterWidget *ui;
    Local_LineEdit * username_lineEdit {username_lineEdit=nullptr};//定义用户名输入框
    Local_LineEdit * password1_lineEdit {password1_lineEdit=nullptr};//定义口令1输入框
    Local_LineEdit * password2_lineEdit {password2_lineEdit=nullptr};//定义口令2输入框
    bool capskeystat {capskeystat = false};//大小写按钮状态

    QNetworkAccessManager *manager{ manager = nullptr };
    QNetworkReply *post_reply{ post_reply = nullptr };

    QRegExp *lowercase = new QRegExp("^.*[a-z]+.*$");
    QRegExp *uppercase = new QRegExp("^.*[A-Z]+.*$");
    QRegExp *numbercase = new QRegExp("^.*[0-9]+.*$");
    QRegExp *speccharcase = new QRegExp("^.*[`~!@#$%^&*()_+<>?{},.]+.*$");
    QRegExp *usernameRange = new QRegExp("^[a-zA-Z0-9]+$");
    QRegExp *passwordRange = new QRegExp("^[a-zA-Z0-9`~!@#$%^&*()_+<>?{},.]+$");

    bool checkUsernameRegular();
    bool checkPassword1Regular();
    bool checkPassword2Regular();
    bool CapsButtonState();
    void checkUsernameExistence();
};

#endif // USERREGISTERWIDGET_H
