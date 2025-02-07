#include "metadata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Metadata w;
    w.show();

    return a.exec();
}
