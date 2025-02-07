#include "cipherindex.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CipherIndex w;
    w.show();

    return a.exec();
}
