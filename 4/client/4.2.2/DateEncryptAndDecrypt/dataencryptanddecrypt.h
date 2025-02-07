#ifndef DATAENCRYPTANDDECRYPT_H
#define DATAENCRYPTANDDECRYPT_H

#include <QMainWindow>
#include <QUuid>
#include <QDebug>
#include <QDir>
#include "lib/include/cipherinterface.h"


namespace Ui {
class dataencryptanddecrypt;
}

class dataencryptanddecrypt : public QMainWindow
{
    Q_OBJECT

public:
    explicit dataencryptanddecrypt(QWidget *parent = nullptr);
    ~dataencryptanddecrypt();

private:
    Ui::dataencryptanddecrypt *ui;
};

#endif // DATAENCRYPTANDDECRYPT_H
