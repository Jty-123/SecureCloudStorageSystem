#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    translator = new QTranslator(qApp);
    ui->message_label->setText(tr("返回结果"));
    ui->menu->addAction(tr("中文"), this, SLOT(On_Chinese()));
    ui->menu->addAction(tr("English"), this, SLOT(On_English()));
}

void MainWindow::On_Chinese(){
    translator->load(QString(":/translate/cn"));
    QApplication::installTranslator(translator);
    ui->retranslateUi(this);
    ui->message_label->setText(tr("返回结果"));

}
void MainWindow::On_English(){
    QApplication::removeTranslator(translator);
    translator->load(QString(":/translate/en"));
    QApplication::installTranslator(translator);
    ui->retranslateUi(this);
    ui->message_label->setText(tr("返回结果"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
