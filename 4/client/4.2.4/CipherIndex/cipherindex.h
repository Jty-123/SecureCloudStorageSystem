#ifndef CIPHERINDEX_H
#define CIPHERINDEX_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>
#include <QUuid>
#include <QDebug>
#include "lib/include/cipherinterface.h"
namespace Ui {
class CipherIndex;
}

class CipherIndex : public QMainWindow
{
    Q_OBJECT

public:
    explicit CipherIndex(QWidget *parent = nullptr);
    ~CipherIndex();

public slots:

    void slot_qprogress_finished(int, QProcess::ExitStatus);
    void slot_qprogress_readyReadStandardOutput();
    void slot_qprogress_started();

private:
    Ui::CipherIndex *ui;
    QString doc_plaintext;
    QString file_unique_id = "";
};

#endif // CIPHERINDEX_H
