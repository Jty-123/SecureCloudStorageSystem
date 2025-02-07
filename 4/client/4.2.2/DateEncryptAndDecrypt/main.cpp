#include "dataencryptanddecrypt.h"
#include <QApplication>
#include "./lib/include/cipherinterface.h"
#include <QUuid>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataencryptanddecrypt w;
    w.show();

    return a.exec();
}
