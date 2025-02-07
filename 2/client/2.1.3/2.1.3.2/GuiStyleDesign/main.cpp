#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QFile file(QString(":/resource/prefix/resource/qss/style.qss"));
//    file.open(QFile::ReadOnly);
//    QString qss = QLatin1String(file.readAll());
//    qApp->setStyleSheet(qss);
//    file.close();

    qApp->setWindowIcon(QIcon(":/resource/prefix/resource/pic/app.ico"));
    MainWindow w;
    w.show();


    return a.exec();
}
