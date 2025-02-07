#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (nullptr == manager) {
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(slot_replyFinished(QNetworkReply*)));
        connect(manager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
                this, SLOT(slot_sslErrors(QNetworkReply*, QList<QSslError>)));
        connect(manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
                this, SLOT(slot_provideAuthenication(QNetworkReply*, QAuthenticator*)));
    }
    QNetworkRequest network_request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    network_request.setSslConfiguration(config);
    network_request.setUrl(QUrl("http://www.sklois.cn/"));
    get_reply = manager->get(network_request);

    connect(get_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slot_NetWorkError(QNetworkReply::NetworkError)));
}
void MainWindow::slot_replyFinished(QNetworkReply* reply){
    QString ret_data;
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    if (nullptr != reply) {
        ret_data = reply->readAll();
        qDebug() << Q_FUNC_INFO << "reply readAll is " << ret_data;
        reply->deleteLater();
        reply = nullptr;
    }
}

void MainWindow::slot_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    QSslCertificate sslcert = errors[0].certificate();
    reply->ignoreSslErrors();
}

void MainWindow::slot_provideAuthenication(QNetworkReply* reply, QAuthenticator* authenticator) {

}

void MainWindow::slot_NetWorkError(QNetworkReply::NetworkError errorCode) {
    if (nullptr != get_reply) {
        get_reply->deleteLater();
        get_reply = nullptr;
    }
    if (nullptr != manager) {
        delete manager;
        manager = nullptr;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


