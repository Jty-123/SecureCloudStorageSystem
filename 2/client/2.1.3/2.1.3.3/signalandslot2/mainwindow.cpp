#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this,SIGNAL(send(QString)),this,SLOT(receive(QString)));
    emit send("message");
}
void MainWindow::receive(QString para)
{
    qDebug()<<"receive para is "<<para;
}
MainWindow::~MainWindow()
{
    delete ui;
}
