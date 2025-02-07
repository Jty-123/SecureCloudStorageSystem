#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    library = new Library();
    int out = library->add(10,19);
    qDebug()<<"out is "<<out;
}

MainWindow::~MainWindow()
{
    delete ui;
}
