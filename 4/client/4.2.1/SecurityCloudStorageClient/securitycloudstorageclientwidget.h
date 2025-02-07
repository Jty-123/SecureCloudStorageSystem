#ifndef SECURITYCLOUDSTORAGECLIENTWIDGET_H
#define SECURITYCLOUDSTORAGECLIENTWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>
#include <QMenu>
#include <QSequentialAnimationGroup>
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include <QUuid>
#include <QProcess>
#include <QListWidgetItem>
#include <QThread>
#include <QtTest>
#include "./local_lineedit/local_lineedit.h"

namespace Ui {
class SecurityCloudStorageClientWidget;
}

class SecurityCloudStorageClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecurityCloudStorageClientWidget(QWidget *parent = nullptr);
    ~SecurityCloudStorageClientWidget();

private slots:
    void on_document_management_pushButton_clicked();
        void on_transport_list_pushButton_clicked();
        void on_share_list_pushButton_clicked();
        void on_document_search_pushButton_clicked();
        void on_search_tabWidget_goto_normal_pushButton_clicked();

        void on_search_tabWidget_goto_advanced_pushButton_clicked();

        void slot_namesearch_clicked();
        void slot_ciphersearch_clicked();


        void slot_search_tabWidget_namesearch_clicked();
        void slot_search_tabWidget_ciphersearch_clicked();

        void slot_searchpage_search_linedit_focussed(bool);


protected:

private:
    Ui::SecurityCloudStorageClientWidget *ui;

    Local_LineEdit *searchpage_search_linedit {searchpage_search_linedit = nullptr};



};

#endif // SECURITYCLOUDSTORAGECLIENTWIDGET_H
