#include "securitycloudstorageclientwidget.h"
#include "ui_securitycloudstorageclientwidget.h"

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

    ui->notice_label->setVisible(false);



    if(nullptr==searchpage_search_linedit){
        searchpage_search_linedit = new Local_LineEdit();
        searchpage_search_linedit->setMinimumHeight(40);
        searchpage_search_linedit->setMinimumWidth(539);
        searchpage_search_linedit->setStyleSheet("QLineEdit:{font: 12pt \"微软雅黑\"; min-height: 26px;min-height: 270px}");
        searchpage_search_linedit->setPlaceholderText("多个词之间以“&”或“|”间隔，表示“与”或“或”的关系");
        searchpage_search_linedit->setToolTip("多个词之间以“&”或“|”间隔，表示“与”或“或”的关系");
        connect(searchpage_search_linedit,
                SIGNAL(signal_linedit_focussed(bool )),
                this,SLOT(slot_searchpage_search_linedit_focussed(bool)));
        ui->main_search_horizontalLayout->addWidget(searchpage_search_linedit);
    }


    QMenu *search_tabWidget_select_menu = new QMenu();
    QAction *search_tabWidget_name_search = new QAction("文件名检索");
    QAction *search_tabWidget_cipher_search = new QAction("密文检索");
    search_tabWidget_select_menu->addAction(search_tabWidget_name_search);
    search_tabWidget_select_menu->addAction(search_tabWidget_cipher_search);
    connect(search_tabWidget_name_search,SIGNAL(triggered()),this,SLOT(slot_search_tabWidget_namesearch_clicked()));
    connect(search_tabWidget_cipher_search,SIGNAL(triggered()),this,SLOT(slot_search_tabWidget_ciphersearch_clicked()));
    ui->search_select_pushButton->setMenu(search_tabWidget_select_menu);

    ui->search_tabWidget->setTabsClosable(true);
    ui->search_tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);


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

void SecurityCloudStorageClientWidget::slot_searchpage_search_linedit_focussed(bool stat){

}
