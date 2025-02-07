#include "cipherindex.h"
#include "ui_cipherindex.h"

CipherIndex::CipherIndex(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CipherIndex)
{
    ui->setupUi(this);

    QString homepath =QDir::currentPath();
    qDebug()<<"homepath ="<< homepath;
    QString plaintextpath = homepath + "/plaintextpath/plaintext.docx";//明文路径
    QString frompath = plaintextpath;
    if (frompath.endsWith(".txt") ||
            frompath.endsWith(".doc", Qt::CaseInsensitive) ||
            frompath.endsWith(".docx", Qt::CaseInsensitive) ||
            frompath.endsWith(".ppt", Qt::CaseInsensitive) ||
            frompath.endsWith(".pptx", Qt::CaseInsensitive) ||
            frompath.endsWith(".xlsx", Qt::CaseInsensitive) ||
            frompath.endsWith(".xls", Qt::CaseInsensitive) ||
            frompath.endsWith(".pdf", Qt::CaseInsensitive) ||
            frompath.endsWith(".html", Qt::CaseInsensitive) ||
            frompath.endsWith(".rtf", Qt::CaseInsensitive) ||
            frompath.endsWith(".odt", Qt::CaseInsensitive) ||
            frompath.endsWith(".ods", Qt::CaseInsensitive) ||
            frompath.endsWith(".odp", Qt::CaseInsensitive)||
            frompath.endsWith(".odg", Qt::CaseInsensitive)
            ) {
        QString configPath;
        QDir dir;
        configPath = dir.currentPath();
        QProcess * _mprogress = new QProcess();
        connect(_mprogress, SIGNAL(finished(int, QProcess::ExitStatus)),
                this, SLOT(slot_qprogress_finished(int, QProcess::ExitStatus)));
        connect(_mprogress, SIGNAL(readyReadStandardOutput()),
                this, SLOT(slot_qprogress_readyReadStandardOutput()));
        connect(_mprogress, SIGNAL(started()),
                this, SLOT(slot_qprogress_started()));
#ifdef Q_OS_MAC
        // mac
        QString doctotextpath = "sh " + configPath + "/doctotext/doctotext.sh "+frompath;
        qDebug() << "doctotextpath is " <<doctotextpath;
        //qDebug() << "frompath is " <<frompath;
        // _mprogress->start(doctotextpath ,QStringList(frompath));
        _mprogress->start(doctotextpath);
        qDebug() << "开始doctotext ";
#endif

#ifdef Q_OS_LINUX
        // linux
        QString doctotextpath = "sh " + configPath + "/doctotext/doctotext.sh "+frompath;
        qDebug() << "doctotextpath is " <<doctotextpath;
        //qDebug() << "frompath is " <<frompath;
        // _mprogress->start(doctotextpath ,QStringList(frompath));
        _mprogress->start(doctotextpath);
        qDebug() << "开始doctotext ";
#endif

#ifdef Q_OS_WIN32
        // win
        QString doctotextpath = configPath + "/doctotext/doctotext.exe";
        qDebug() << "doctotextpath is " <<doctotextpath;
        qDebug() << "frompath is " <<frompath;
        _mprogress->start(doctotextpath ,QStringList(frompath));
#endif
    }else{
        qDebug() << "无法对此类型的文件生成索引" ;
    }
}

void CipherIndex::slot_qprogress_started() {
    qDebug() << "Proc Started";
}
void CipherIndex::slot_qprogress_readyReadStandardOutput() {
    qDebug() << "readyOut";
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();
    QString docout = QString(buf);
    doc_plaintext = doc_plaintext + docout;
    // YunLock_UploadCipherIndex();
}



void CipherIndex::slot_qprogress_finished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Finished: " << exitCode <<"doc_plaintext length is "<<doc_plaintext.length();
    file_unique_id = "be182c4c625d400f976165c3af4fc12e";
    string cipherindex = YunLock_GenerateCipherIndex(
                doc_plaintext.toStdString(),
                this->file_unique_id.toStdString());
    QString cipherindexstr = QString::fromStdString(cipherindex);
    qDebug()<<Q_FUNC_INFO<<cipherindexstr;
    qDebug()<<("密文索引生成完成");

}

CipherIndex::~CipherIndex()
{
    delete ui;
}
