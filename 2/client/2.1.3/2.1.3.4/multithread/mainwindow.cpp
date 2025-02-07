#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread *sonthread=nullptr;
    SonObject *sonobject=nullptr;
    if(nullptr==sonthread){
        sonthread = new QThread();
    }
    if(nullptr==sonobject){
        sonobject = new SonObject();
        connect(sonobject, SIGNAL(sendsignal(QString)),
                this, SLOT(receiveslot(QString)));
        sonobject->DoSetup(*sonthread);
        sonobject->moveToThread(sonthread);
    }
    if (!sonthread->isRunning()) {
        sonthread->start();
    }



}

void MainWindow::receiveslot(QString message){
    qDebug()<<"receive message is "<<message;
}

MainWindow::~MainWindow()
{

    delete ui;
}
