#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mypushButton->setStyleSheet("QPushButton{border-radius:5px;background-image:url(:/resource/prefix/resource/pic/button_default.png);}"
                                    "QPushButton:hover{background-image:url(:/resource/prefix/resource/pic/button_hover.png);}"
                                    "QPushButton:pressed{background-image:url(:/resource/prefix/resource/pic/button_pressed.png);}");

//    setStyleSheet("QPushButton{border-radius:5px;background-image:url(:/resource/prefix/resource/pic/button_default.png);}"
//                                        "QPushButton:hover{background-image:url(:/resource/prefix/resource/pic/button_hover.png);}"
//                                        "QPushButton:pressed{background-image:url(:/resource/prefix/resource/pic/button_pressed.png);}");



}

MainWindow::~MainWindow()
{
    delete ui;
}
