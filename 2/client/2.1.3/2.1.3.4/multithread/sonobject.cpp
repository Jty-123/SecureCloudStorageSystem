#include "sonobject.h"

SonObject::SonObject(QObject *parent) : QObject(parent)
{
}
void SonObject::DoSetup(QThread &cThread ){
    connect(&cThread,SIGNAL(started()),this,SLOT(operation()));
}
void SonObject::operation(){
    for(int i = 0; i < 10; i ++)
    {
        QEventLoop eventloop;
        QTimer::singleShot(1000, &eventloop, SLOT(quit())); //wait 1s
        eventloop.exec();
        qDebug()<<"tick";
    }
    emit sendsignal("complete!");
}
