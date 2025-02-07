#include "securitycloudstorageclientwidget.h"
#include "ui_securitycloudstorageclientwidget.h"
#include "./lib/include/cipherinterface.h"
SecurityCloudStorageClientWidget::SecurityCloudStorageClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecurityCloudStorageClientWidget)
{
    ui->setupUi(this);
    ui->main_stackedWidget->setCurrentIndex(0);


    QMenu *select_menu = new QMenu(); //初始化一个QMenu
    QAction *name_search = new QAction("文件名检索"); //为Memu添加"文件名检索"菜单
    QAction *cipher_search = new QAction("密文检索");//为Memu添加"密文检索"菜单
    select_menu->addAction(name_search);//将"文件名检索"菜单添加到QMenu中
    select_menu->addAction(cipher_search); //将"密文检索"菜单添加到QMenu中
    connect(name_search,SIGNAL(triggered()),this,SLOT(slot_namesearch_clicked()));//连接信号与槽函数，设置鼠标点击"文件名检索"菜单响应
    connect(cipher_search,SIGNAL(triggered()),this,SLOT(slot_ciphersearch_clicked()));//连接信号与槽函数，设置鼠标点击"密文检索"菜单响应
    ui->select_pushButton->setMenu(select_menu); //将QMenu添加到检索切换按钮上


    ui->select_pushButton->setMenu(select_menu);


    QMenu *search_tabWidget_select_menu = new QMenu();
    QAction *search_tabWidget_name_search = new QAction("文件名检索");
    QAction *search_tabWidget_cipher_search = new QAction("密文检索");
    search_tabWidget_select_menu->addAction(search_tabWidget_name_search);
    search_tabWidget_select_menu->addAction(search_tabWidget_cipher_search);
    connect(search_tabWidget_name_search,SIGNAL(triggered()),this,SLOT(slot_search_tabWidget_namesearch_clicked()));
    connect(search_tabWidget_cipher_search,SIGNAL(triggered()),this,SLOT(slot_search_tabWidget_ciphersearch_clicked()));
    ui->search_select_pushButton->setMenu(search_tabWidget_select_menu);
    ui->search_select_pushButton->setMenu(search_tabWidget_select_menu);

    ui->search_tabWidget->setTabsClosable(true);
    ui->search_tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    if (nullptr == uploadentityhash) {
        uploadentityhash = new QMap<QString, UploadFileEntity*>;
    }

}

SecurityCloudStorageClientWidget::~SecurityCloudStorageClientWidget()
{
    delete ui;
}


void SecurityCloudStorageClientWidget::slot_namesearch_clicked(){
    ui->search_pushButton->setText("文件名检索");//将检索按钮上的字符串修改为"文件名检索"
}
void SecurityCloudStorageClientWidget::slot_ciphersearch_clicked(){
    ui->search_pushButton->setText("密文检索");//将检索按钮上的字符串修改为"密文检索"
}

void SecurityCloudStorageClientWidget::slot_search_tabWidget_namesearch_clicked(){
    ui->search_tabWidget_search_pushButton->setText("文件名检索");
}

void SecurityCloudStorageClientWidget::slot_search_tabWidget_ciphersearch_clicked(){
    ui->search_tabWidget_search_pushButton->setText("密文检索");
}


void SecurityCloudStorageClientWidget::on_document_management_pushButton_clicked()
{
    ui->main_stackedWidget->setCurrentIndex(0);

    ui->document_management_pushButton->
            setStyleSheet(
                "QPushButton#document_management_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shuju_en.png);"
                "}"
                "QPushButton#document_management_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_hua.png);"
                "}"
                "QPushButton#document_management_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_en.png);"
                "}"
                );
    ui->document_search_pushButton->
            setStyleSheet(
                "QPushButton#document_search_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_mo.png);"
                "}"
                "QPushButton#document_search_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_hua.png);"
                "}"
                "QPushButton#document_search_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_en.png);"
                "}"
                );
    ui->transport_list_pushButton->
            setStyleSheet(
                "QPushButton#transport_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_mo.png);"
                "}"
                "QPushButton#transport_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_hua.png);"
                "}"
                "QPushButton#transport_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_en.png);"
                "}"
                );

    ui->share_list_pushButton->
            setStyleSheet(
                "QPushButton#share_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_mo.png);"
                "}"
                "QPushButton#share_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_hua.png);"
                "}"
                "QPushButton#share_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_en.png);"
                "}"
                );



}

void SecurityCloudStorageClientWidget::on_document_search_pushButton_clicked()
{
    ui->main_stackedWidget->setCurrentIndex(1);
    ui->normal_search_widget->setVisible(true);//设置普通检索QWidget为可见
    ui->advanced_search_widget->setVisible(false); //设置高级检索QWidget为不可见
    ui->document_management_pushButton->
            setStyleSheet(
                "QPushButton#document_management_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shuju_mo.png);"
                "}"
                "QPushButton#document_management_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_hua.png);"
                "}"
                "QPushButton#document_management_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_en.png);"
                "}"
                );
    ui->document_search_pushButton->
            setStyleSheet(
                "QPushButton#document_search_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_en.png);"
                "}"
                "QPushButton#document_search_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_hua.png);"
                "}"
                "QPushButton#document_search_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_en.png);"
                "}"
                );
    ui->transport_list_pushButton->
            setStyleSheet(
                "QPushButton#transport_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_mo.png);"
                "}"
                "QPushButton#transport_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_hua.png);"
                "}"
                "QPushButton#transport_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_en.png);"
                "}"
                );

    ui->share_list_pushButton->
            setStyleSheet(
                "QPushButton#share_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_mo.png);"
                "}"
                "QPushButton#share_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_hua.png);"
                "}"
                "QPushButton#share_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_en.png);"
                "}"
                );
}

void SecurityCloudStorageClientWidget::on_transport_list_pushButton_clicked()
{
    ui->main_stackedWidget->setCurrentIndex(2);

    ui->document_management_pushButton->
            setStyleSheet(
                "QPushButton#document_management_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shuju_mo.png);"
                "}"
                "QPushButton#document_management_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_hua.png);"
                "}"
                "QPushButton#document_management_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_en.png);"
                "}"
                );
    ui->document_search_pushButton->
            setStyleSheet(
                "QPushButton#document_search_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_mo.png);"
                "}"
                "QPushButton#document_search_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_hua.png);"
                "}"
                "QPushButton#document_search_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_en.png);"
                "}"
                );
    ui->transport_list_pushButton->
            setStyleSheet(
                "QPushButton#transport_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_en.png);"
                "}"
                "QPushButton#transport_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_hua.png);"
                "}"
                "QPushButton#transport_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_en.png);"
                "}"
                );

    ui->share_list_pushButton->
            setStyleSheet(
                "QPushButton#share_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_mo.png);"
                "}"
                "QPushButton#share_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_hua.png);"
                "}"
                "QPushButton#share_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_en.png);"
                "}"
                );
}

void SecurityCloudStorageClientWidget::on_share_list_pushButton_clicked()
{
    ui->main_stackedWidget->setCurrentIndex(3);
    ui->document_management_pushButton->
            setStyleSheet(
                "QPushButton#document_management_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shuju_mo.png);"
                "}"
                "QPushButton#document_management_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_hua.png);"
                "}"
                "QPushButton#document_management_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shuju_en.png);"
                "}"
                );
    ui->document_search_pushButton->
            setStyleSheet(
                "QPushButton#document_search_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_mo.png);"
                "}"
                "QPushButton#document_search_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_hua.png);"
                "}"
                "QPushButton#document_search_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/shujujiansuo_en.png);"
                "}"
                );
    ui->transport_list_pushButton->
            setStyleSheet(
                "QPushButton#transport_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_mo.png);"
                "}"
                "QPushButton#transport_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_hua.png);"
                "}"
                "QPushButton#transport_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/chuanshu_en.png);"
                "}"
                );

    ui->share_list_pushButton->
            setStyleSheet(
                "QPushButton#share_list_pushButton{"
                "border-radius:0px;"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_en.png);"
                "}"
                "QPushButton#share_list_pushButton:hover{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_hua.png);"
                "}"
                "QPushButton#share_list_pushButton:pressed{"
                "background-image: url(:/pic/resource/img/titlebar/fenxiang_en.png);"
                "}"
                );
}




void SecurityCloudStorageClientWidget::on_search_tabWidget_goto_normal_pushButton_clicked()
{
    ui->normal_search_widget->setVisible(true);//设置普通检索QWidget为可见
    ui->advanced_search_widget->setVisible(false); //设置高级检索QWidget为不可见

}

void SecurityCloudStorageClientWidget::on_search_tabWidget_goto_advanced_pushButton_clicked()
{
    ui->normal_search_widget->setVisible(false);//设置普通检索QWidget为可见
    ui->advanced_search_widget->setVisible(true); //设置高级检索QWidget为不可见
}

void SecurityCloudStorageClientWidget::on_fileupload_pushButton_clicked()

{
    QString parentid = "根目录";
    QFileDialog fileDialog(this);//初始化QFileDialog
        fileDialog.setFileMode(QFileDialog::ExistingFiles);//设置可以同时选择多个文件
        QStringList filters;//定义一个过滤器
        filters << "所有文件(*)";//过滤器设置为"所有文件(*)"，表示这个文件选择框可以选择任意文件
        fileDialog.setNameFilters(filters); //为QFileDialog设置过滤器
        if (fileDialog.exec() == QDialog::Accepted) //弹出对话框
        {
            QStringList strPathList = fileDialog.selectedFiles();//用户点击确认时，返回被选中文件的列表
            for(int i = 0; i< strPathList.size();++i) //遍历文件列表
            {
                /*将需要上传的文件添加到上传文件列表中*/
                QString plaintextpath = strPathList.at(i);
                UploadFileEntity *uploadfileentity = new UploadFileEntity(plaintextpath,parentid);
                uploadentityhash->insert(plaintextpath,uploadfileentity);
            }
            refreshuploadlistview();
        }

}

void SecurityCloudStorageClientWidget::refreshuploadlistview(){

    //    qDebug()<<Q_FUNC_INFO<<"in refreshuploadlistview";
    if (nullptr != uploadentityhash&&uploadentityhash->size() > 0) {
        QMap<QString, UploadFileEntity*>::const_iterator iterater = uploadentityhash->constBegin();
        while (iterater != uploadentityhash->constEnd()) {
            //            qDebug()<<Q_FUNC_INFO<<"in while";
            QString uploadfilelistkey = iterater.key();
            UploadFileEntity* uploadfileentity = iterater.value();
            QListWidgetItem *uploaditem= uploadfileentity->getuploaditem();
            uploaditem->setSizeHint(QSize(uploaditem->sizeHint().width(), 60));
            UploadListForm *uploadlistform = uploadfileentity->getuploadlistform();
            ui->uploadlist_listWidget->addItem(uploaditem);
            ui->uploadlist_listWidget->setItemWidget(uploaditem, uploadlistform);
            uploadfileentity->start();
            iterater++;
        }
    }
}
