#include "securitycloudstorageclientwidget.h"
#include "./Login/loginwidget.h"
#include <QApplication>
#include <QFile>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    SecurityCloudStorageClientWidget w;
//    w.show();
    LoginWidget loginwidget;
    loginwidget.show();



    QFile file(QString(":/pic/resource/style.qss"));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());

    qDebug()<<QSslSocket::supportsSsl();
     qDebug()<<QSslSocket::sslLibraryVersionString();
    qApp->setStyleSheet(qss);



    return a.exec();
}
