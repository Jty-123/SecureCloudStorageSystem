#ifndef METADATA_H
#define METADATA_H

#include <QMainWindow>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QUuid>
#include <QDebug>
//#include "./jsonlib/json.h"
#include "./inc/sha256.h"
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


//using QtJson::JsonObject;
//using QtJson::JsonArray;

namespace Ui {
class Metadata;
}

class Metadata : public QMainWindow
{
    Q_OBJECT

public:
    explicit Metadata(QWidget *parent = nullptr);

    void generateMetadata();
    QString calcfilehash(QString path, QString alg_method);
    QString calcstrhash(QString input);

    ~Metadata();

private:
    Ui::Metadata *ui;

    QString filepath;
    QString cipherpath;
    QString encryptkey;
//    JsonObject metadatajsonobj;//初始化json对象
    QString metadata = "";

    /*	缓冲区大小*/
    #define BUFFER_SIZE 1024

};

#endif // METADATA_H
