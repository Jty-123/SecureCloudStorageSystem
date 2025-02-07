#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->label_Caps->hide();
    if(nullptr==lineEdit_password){
        lineEdit_password = new Local_LineEdit();
        connect(lineEdit_password,
                SIGNAL(signal_linedit_focussed(bool )),
                this,SLOT(slot_password_linedit_focussed(bool)));

        lineEdit_password->setText("");
        ui->lineEdit_password_horizontalLayout->addWidget(lineEdit_password);
    }
    this->lineEdit_password->setMinimumHeight(30);
    this->lineEdit_password->setMinimumWidth(240);

    this->lineEdit_password->setEchoMode(QLineEdit::Password);

    setTabOrder(this->lineEdit_password,ui->pushButton_Login);
    setTabOrder(ui->pushButton_Login,ui->pushButton);

    //读取密文文件存储路径
    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/resource/img/resource/img/background_img2.jpg").scaled(// 缩放背景图.
                                                                                              this->size(),
                                                                                              Qt::IgnoreAspectRatio,
                                                                                              Qt::SmoothTransformation)));
    this->setPalette(palette);                           // 给widget加上背景图


    //    ui->authcode_label->installEventFilter(this);

    setTabOrder(ui->lineEdit_username,this->lineEdit_password);
    setTabOrder(this->lineEdit_password,ui->authcode_lineedit);

    refreshcode();

}


void LoginWidget::refreshcode(){
    if (nullptr == login_manager) {
        login_manager = new QNetworkAccessManager(this);
        connect(login_manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(slot_replyFinished(QNetworkReply*)));
        connect(login_manager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
                this, SLOT(slot_sslErrors(QNetworkReply*, QList<QSslError>)));
        connect(login_manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
                this, SLOT(slot_provideAuthenication(QNetworkReply*, QAuthenticator*)));
    }
    QNetworkRequest network_request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    network_request.setSslConfiguration(config);
    network_request.setUrl(QUrl("https://127.0.0.1:9443/userauthinit"));

    network_request.setRawHeader("Content-Type", "application/json");
    //    JsonObject messagejsonobj;
    QVariantMap messagejsonvar;
    messagejsonvar.insert("method", "userauthinit");
    messagejsonvar.insert("version", "1.0");
    messagejsonvar.insert("timestamp", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QJsonObject obJct = QJsonObject::fromVariantMap(messagejsonvar);
    QJsonDocument jsonDoc(obJct);
    QByteArray json = jsonDoc.toJson();
    QString messagejsonstr(json);

    qDebug()<<Q_FUNC_INFO<<"messagejsonstr is "<<messagejsonstr;
    login_post_reply = login_manager->post(network_request,messagejsonstr.toUtf8());
    connect(login_post_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slot_NetWorkError(QNetworkReply::NetworkError)));
}

void LoginWidget::slot_replyFinished(QNetworkReply* reply){
    QByteArray ret_data;
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() <<Q_FUNC_INFO<< "status code=" << statusCode.toInt();
    QString method="";
    QString result="";
    QString code = "";

    QString message = "";
    QVariantMap details;
    bool ifexist;
    if (nullptr != reply) {



        QString method = (QString)reply->rawHeader("method");
        if(0==method.compare("userauthinit")){
            this->random = (QString)reply->rawHeader("randomcode");
            qDebug() <<Q_FUNC_INFO<< "random is " << this->random;
            ret_data = reply->readAll();
            QPixmap pix;
            pix.loadFromData(ret_data);
            ui->authcode_label->setPixmap(pix);
        }else if(0==method.compare("userauth")){
            ret_data = reply->readAll();
            qDebug() <<Q_FUNC_INFO<< "ret_data is " << ret_data;

        }else{
            QString debugret_data = reply->readAll();
            qDebug() <<Q_FUNC_INFO<< "debugret_data is " << debugret_data;
        }
    }
}

void LoginWidget::slot_sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    QSslCertificate sslcert = errors[0].certificate();
    reply->ignoreSslErrors();
}

void LoginWidget::slot_provideAuthenication(QNetworkReply* reply, QAuthenticator* authenticator) {

}

void LoginWidget::slot_NetWorkError(QNetworkReply::NetworkError errorCode) {


    if (nullptr != login_post_reply) {
        login_post_reply->deleteLater();
        login_post_reply = nullptr;
    }
    if (nullptr != login_manager) {
        delete login_manager;
        login_manager = nullptr;
    }
}



void LoginWidget::slot_password_linedit_focussed(bool stat){

}



void LoginWidget::userlogin(QString username,QString password,QString role ,QString authcode){
    if (nullptr == login_manager) {
        login_manager = new QNetworkAccessManager(this);
        connect(login_manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(slot_replyFinished(QNetworkReply*)));
        connect(login_manager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
                this, SLOT(slot_sslErrors(QNetworkReply*, QList<QSslError>)));
        connect(login_manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
                this, SLOT(slot_provideAuthenication(QNetworkReply*, QAuthenticator*)));
    }
    QNetworkRequest network_request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    network_request.setSslConfiguration(config);
    network_request.setUrl(QUrl("https://127.0.0.1:9443/userauth"));
    network_request.setRawHeader("Content-Type", "application/json");

    QVariantMap messagejsonvar;
    messagejsonvar.insert("method", "userauth");
    messagejsonvar.insert("version", "1.0");
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    messagejsonvar.insert("timestamp", timestamp);

    QVariantMap requestvar;
    requestvar.insert("username", username);
    requestvar.insert("authcode", authcode);
    requestvar.insert("role", role);

    QString macvalue = "";
    if(random.length()>0){
        QString digestinput = username+"&"+authcode.toLower()+"&"+this->random+"&"+timestamp;
        qDebug()<<Q_FUNC_INFO<<"digestinput is "<<digestinput;
        QString saltpassword  = saltvalue + digest(password);
        uint8 hmackey[33] = "\0";
        QByteArray saltpasswordbyte=saltpassword.toUtf8();
        uint8 * inputbyte = reinterpret_cast <unsigned char*>(saltpasswordbyte.data());
        sha256(hmackey,inputbyte,saltpasswordbyte.length());
        //        char digesthex[64];
        //        int i =0;
        //        for (i = 0; i < 32; i++)
        //        {
        //            sprintf(digesthex + 2*i, "%02X ", (unsigned char)digest[i]);
        //        }
        //        QByteArray keyhex(digesthex);
        //        qDebug()<<Q_FUNC_INFO<<"keyhex is "<<keyhex;

        uint8 hmacsha256digest[33] = "\0";
        char hmacsha256base64digest[46] = "\0";
        QByteArray inputbytearray=digestinput.toUtf8();
        hmac_sha256((char* )hmackey,32,
                    inputbytearray.data(),inputbytearray.length(),
                    hmacsha256digest);
        base64enc(hmacsha256base64digest,hmacsha256digest,32);
        macvalue=QString(hmacsha256base64digest);
        qDebug()<<Q_FUNC_INFO<<"macvalue is "<<macvalue;

    }
    requestvar.insert("mac", macvalue);
    messagejsonvar.insert("request", requestvar);

    QJsonObject obJct = QJsonObject::fromVariantMap(messagejsonvar);
    QJsonDocument jsonDoc(obJct);
    QByteArray json = jsonDoc.toJson();
    QString messagejsonstr(json);

    qDebug()<<Q_FUNC_INFO<<"messagejsonstr is "<<messagejsonstr;
    login_post_reply = login_manager->post(network_request,messagejsonstr.toUtf8());
    connect(login_post_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slot_NetWorkError(QNetworkReply::NetworkError)));
}


QString LoginWidget::digest(QString input){
    if(nullptr==input||input.length()<=0){
        return nullptr;
    }
    uint8 digest[33] = "\0";
    char base64digest[46] = "\0";
    QByteArray bytearray=input.toUtf8();
    uint8 * inputbyte = reinterpret_cast <unsigned char*>(bytearray.data());
    sha256(digest,inputbyte,bytearray.length());
    base64enc(base64digest,digest,32);
    QString base64digeststr(base64digest);
    return base64digeststr;
}

void LoginWidget::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = this->lineEdit_password->text();
    QString authcode = ui->authcode_lineedit->text();
    //    username = "username";
    //    password = "password";
    //    authcode = "authcode";
//    QString role = "安全保密管理员";
//        QString role = "系统管理员";
    //    QString role = "安全审计员";
                QString role = "普通用户";


    userlogin(username,password,role,authcode);

}
LoginWidget::~LoginWidget()
{
    delete ui;
}
