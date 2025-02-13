#ifndef SYSTEMADMINWIDGET_H
#define SYSTEMADMINWIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QStandardItemModel>
#include "./inc/base64_enc.h"
#include <string.h>
#include <stdlib.h>
#include <QDebug>


namespace Ui {
class SystemAdminWidget;
}

class SystemAdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemAdminWidget(QWidget *parent = 0);
    ~SystemAdminWidget();

private slots:
    void on_system_management_pushButton_clicked();


    void slot_replyFinished(QNetworkReply* reply);
    void slot_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void slot_provideAuthenication(QNetworkReply* reply, QAuthenticator* authenticator);
    void slot_NetWorkError(QNetworkReply::NetworkError);


private:
    Ui::SystemAdminWidget *ui;

    QNetworkAccessManager *manager{ manager = nullptr };
    QNetworkReply *post_reply{ post_reply = nullptr };

    QString username = "systemadmin";
    QString password = "09bd600e-1094-4264-a885-204b7c0e1674";

    void  system_audit();

};

#endif // SYSTEMADMINWIDGET_H
