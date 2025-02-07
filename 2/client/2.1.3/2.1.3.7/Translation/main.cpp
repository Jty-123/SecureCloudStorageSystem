#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTranslator tsor;
//    tsor.load(":/translate/en");
//    a.installTranslator(&tsor);
    MainWindow w;
    w.show();

    return a.exec();
}
