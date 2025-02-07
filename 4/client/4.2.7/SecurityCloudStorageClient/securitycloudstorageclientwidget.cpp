#include "securitycloudstorageclientwidget.h"
#include "ui_securitycloudstorageclientwidget.h"

SecurityCloudStorageClientWidget::SecurityCloudStorageClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecurityCloudStorageClientWidget)
{
    ui->setupUi(this);
    ui->main_stackedWidget->setCurrentIndex(0);

    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,7);
    ui->data_list_tableWidget->setSortingEnabled(true);
    ui->data_list_tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->data_list_tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->data_list_tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->data_list_tableWidget->setRowCount(0);
    ui->data_list_tableWidget->setColumnWidth(0, 40);  //设置列宽
    ui->data_list_tableWidget->setColumnWidth(1, 130);


    ui->ishare_tableWidget->setSortingEnabled(true);
    ui->ishare_tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->ishare_tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->ishare_tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->ishare_tableWidget->setRowCount(0);
    ui->ishare_tableWidget->setColumnWidth(0, 150);  //设置列宽
    ui->ishare_tableWidget->setColumnWidth(1, 230);
    ui->ishare_tableWidget->setColumnWidth(2, 230);
    ui->ishare_tableWidget->setColumnWidth(3, 230);
    //    ui->ishare_tableWidget->setColumnWidth(4, 230);

    ui->shared_tome_tableWidget->setSortingEnabled(true);
    ui->shared_tome_tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->shared_tome_tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    ui->shared_tome_tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->shared_tome_tableWidget->setRowCount(0);
    ui->shared_tome_tableWidget->setColumnWidth(0, 150);  //设置列宽
    ui->shared_tome_tableWidget->setColumnWidth(1, 230);
    ui->shared_tome_tableWidget->setColumnWidth(2, 230);
    ui->shared_tome_tableWidget->setColumnWidth(3, 230);
    //    ui->shared_tome_tableWidget->setColumnWidth(4, 230);


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

    if(nullptr==local_linedit){
        local_linedit = new Local_LineEdit();
        local_linedit->setValidator(new QIntValidator(1, 1000, this)); //1, 1000为输入的数字值范围
//        connect(local_linedit,
//                SIGNAL(signal_linedit_focussed(bool )),
//                this,SLOT(slot_jumptopage_linedit_focussed(bool)));
        local_linedit->setText(QString::number(current_page+1));
        ui->jumptopage_lineEdit_horizontalLayout->addWidget(local_linedit);
    }
    ui->filelist_tabWidget->setTabsClosable(true);
    ui->filelist_tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);


    if(nullptr==searchpage_search_linedit){
        searchpage_search_linedit = new Local_LineEdit();
        searchpage_search_linedit->setMinimumHeight(40);
        searchpage_search_linedit->setMinimumWidth(539);
        searchpage_search_linedit->setStyleSheet("QLineEdit:{font: 12pt \"微软雅黑\"; min-height: 26px;min-height: 270px}");
        searchpage_search_linedit->setPlaceholderText("多个词之间以“&”或“|”间隔，表示“与”或“或”的关系");
        searchpage_search_linedit->setToolTip("多个词之间以“&”或“|”间隔，表示“与”或“或”的关系");
//        connect(searchpage_search_linedit,
//                SIGNAL(signal_linedit_focussed(bool )),
//                this,SLOT(slot_searchpage_search_linedit_focussed(bool)));
        ui->main_search_horizontalLayout->addWidget(searchpage_search_linedit);
    }
    ui->lastlogintime_label->setText(lashauthtime);
    ui->lastauth_ipaddress_label->setText(lastauthipaddress);
    ui->username_label->setText(username);



    QPixmap pm(80, 80);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black, 1);
    painter.setPen(pen);
    QBrush brush(Qt::red);
    painter.setBrush(brush);
    painter.drawEllipse(0, 0, 80, 80);
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(50);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, 80, 80), Qt::AlignCenter, QString::number(2));
    QIcon myqicon(pm);
    page_size = ui->show_num_comboBox->currentText().toInt();
    if(nullptr==folderstrulist){
        folderstrulist  = new FolderStructureList(current_page,page_size,ui->folder_treeWidget);
        connect(ui->folder_treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)),
                this, SLOT(TreeWidgetItemPressed_Slot(QTreeWidgetItem*, int)));
        connect(folderstrulist, SIGNAL(itemPressed(QTreeWidgetItem*, int)),
                this, SLOT(TreeWidgetItemPressed_Slot(QTreeWidgetItem*, int)));
    }


    if(nullptr==filestrulist){
        filestrulist = new FileStructureList(
                    ui->data_list_tableWidget,
                    ui->page_total_num_label,
                    ui->metadata_totalnum_label,
                    this->current_page,
                    this->page_size,
                    ui->downloadlist_listWidget);
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


        folderstrulist->getfolderstructure();

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

void SecurityCloudStorageClientWidget::TreeWidgetItemPressed_Slot(QTreeWidgetItem * pressedItem, int column){

    qDebug()<<Q_FUNC_INFO<<"in TreeWidgetItemPressed_Slot";

    auto localpressedItem = dynamic_cast<LocalTreeWidgetItem*>(pressedItem);
    if (qApp->mouseButtons() == Qt::RightButton)
    {
        qDebug()<<Q_FUNC_INFO<<"TreeWidgetItemPressed_Slot";
        QMenu *pMenu = new QMenu(this);
        pMenu->addAction(QString("新建文件夹"));
        pMenu->addSeparator();
        pMenu->addAction(QString("重命名"));
        pMenu->exec(QCursor::pos());
    }else if(qApp->mouseButtons() == Qt::LeftButton){
        if(nullptr!=localpressedItem->getfilemetadata()){
            qDebug()<<Q_FUNC_INFO<<localpressedItem->getfilemetadata()->getcurrentid();
            if(nullptr!=filestrulist){
                current_selected_folder_uniqueid = localpressedItem->getfilemetadata()->getcurrentid();
                filestrulist->getfilemetadata(
                            localpressedItem->getfilemetadata()->getcurrentid(),
                            this->current_page,
                            this->page_size);
            }
        }else{
            qDebug()<<Q_FUNC_INFO<< "根目录";
            if(nullptr!=filestrulist){
                current_selected_folder_uniqueid = "根目录";
                filestrulist->getfilemetadata(
                            "根目录",
                            this->current_page,
                            this->page_size);
            }
        }
    }else{
        current_selected_folder_uniqueid = "根目录";
        qDebug()<<Q_FUNC_INFO<< "根目录";
        if(nullptr!=filestrulist){
            filestrulist->getfilemetadata(
                        "根目录",
                        this->current_page,
                        this->page_size);
        }
    }
}
void SecurityCloudStorageClientWidget::on_refresh_pushButton_clicked()
{
    qDebug()<<Q_FUNC_INFO<< "on_refresh_pushButton_clicked";
}
