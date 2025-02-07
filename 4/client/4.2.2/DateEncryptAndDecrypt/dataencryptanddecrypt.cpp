#include "dataencryptanddecrypt.h"
#include "ui_dataencryptanddecrypt.h"
dataencryptanddecrypt::dataencryptanddecrypt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dataencryptanddecrypt)
{
    ui->setupUi(this);


    QString homepath =QDir::currentPath();
    qDebug()<<"homepath ="<< homepath;
    QString plaintextpath = homepath + "/plaintextpath/plaintext.docx";//明文路径
    QString ciphertextpath = homepath + "/cipherpath/ciphertext.docx";//密文路径


    QString uuid = QUuid::createUuid().toString().replace("{","").replace("}","").replace("-","");//调用QUuid的方法生成随机数uuid1
    QString uuid2 = QUuid::createUuid().toString().replace("{","").replace("}","").replace("-","");//调用QUuid的方法生成随机数uuid2
    qDebug()<<"plaintextpath ="<< plaintextpath;
    QString random_str = uuid+uuid2;//拼接以上生成的两个随机数，字符串长度为64
    string encrypt_key =random_str.toStdString();//QString转成标准C++的std::string类型
    qDebug()<<"random_str ="<< random_str;
    string encrypt_ret =  YunLock_EncryptFile
            (plaintextpath.toStdString(),
             ciphertextpath.toStdString(),
             encrypt_key);//调用加密接口
    QString encrypt_retqstr = QString::fromStdString(encrypt_ret);//将接口返回的std::string类型转成QString类型
    qDebug()<<"encrypt_retqstr ="<< encrypt_retqstr;
    qDebug()<<"加密成功";


    QString decrept_key = random_str; //32位解密密钥
//    QString ciphertextpath = homepath + "/cipherpath/ciphertext.docx";
    QString decryptpath = homepath + "/decryptpath/decryptext.docx";//解密路径


    string decrypt_ret =  YunLock_DecryptFile
        (ciphertextpath.toStdString(),
        decryptpath.toStdString(),
        decrept_key.toStdString());//调用解密接口
    QString decrypt_retqstr = QString::fromStdString(decrypt_ret);//将接口返回的std::string类型转成QString类型
    qDebug()<<"decrypt_retqstr ="<< decrypt_retqstr;
    qDebug()<<"解密成功";

}

dataencryptanddecrypt::~dataencryptanddecrypt()
{
    delete ui;
}
