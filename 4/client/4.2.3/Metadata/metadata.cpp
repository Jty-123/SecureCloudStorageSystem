#include "metadata.h"
#include "ui_metadata.h"


Metadata::Metadata(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Metadata)
{
    ui->setupUi(this);


    QString homepath =QDir::currentPath();
    qDebug()<<"homepath ="<< homepath;
    QString plaintextpath = homepath + "/plaintextpath/plaintext.docx";//明文路径
    QString ciphertextpath = homepath + "/cipherpath/ciphertext.docx";//密文路径

    this->filepath = plaintextpath; //明文数据路径
    this->cipherpath = ciphertextpath; //密文数据路径
    this->encryptkey = "1b6bdc983fac4c6b8043edf4a1b1324024b89b1de9884905a34610ad7beacd18"; //数据加密密钥
    generateMetadata();
}

void Metadata::generateMetadata(){

    QFileInfo fileinfo(filepath);  //定义一个明文数据的QFileInfo类
    QFileInfo cipherfileinfo(cipherpath); //定义一个密文数据的QFileInfo类
    QString filename = fileinfo.fileName();//获取明文数据的名字
    long filesize = (long)fileinfo.size();//获取明文数据的大小
    QDateTime ctime = fileinfo.created();//获取明文数据的创建时间
    QDateTime mtime = fileinfo.lastModified();//获取明文数据的最后修改时间
    QDateTime lastaccesstime = fileinfo.lastRead();//获取明文数据的最后访问时间
    QDateTime uploadtime = QDateTime::currentDateTime();//获取当前时间
    QString fileowner = "username"; //设置数据拥有者为全局变量中的username
    QString plaintexthash = calcfilehash(filepath,"sha256");//调用calcfilehash函数对明文数据计算哈希值，这个函数的实现将在下文进行介绍
    QString ciphertexthash = calcfilehash(cipherpath,"sha256");//调用calcfilehash函数对密文数据计算哈希值，这个函数的实现将在下文进行介绍
    QString keyhash = calcstrhash(encryptkey);//调用calcstrhash函数对数据加密密钥计算哈希值
    long ciphertextsize = cipherfileinfo.size();//获得密文数据的大小
    QString type = fileinfo.isFile()?"file":"dir";//设置type为file或者dir类型
    QString currentid = QUuid::createUuid().toString().replace("{",
                                                               "").replace("}","").replace("-","");//使用QUuid获取随机数，设置为当前节点标识

    QVariantMap metadatajsonvar; //初始化QVariantMap对象
    /*…添加其他数据元信息*/
    metadatajsonvar.insert("filename", filename);//设置filename值
    metadatajsonvar.insert("filesize", QString::number(filesize));//设置filesize值
    metadatajsonvar.insert("ctime", ctime);
    metadatajsonvar.insert("mtime", mtime);
    metadatajsonvar.insert("lastaccesstime", lastaccesstime);
    metadatajsonvar.insert("uploadtime", uploadtime);
    metadatajsonvar.insert("fileowner", fileowner);
    metadatajsonvar.insert("plaintexthash", plaintexthash);
    metadatajsonvar.insert("ciphertexthash", ciphertexthash);
    metadatajsonvar.insert("ciphertextsize", QString::number(ciphertextsize));
    metadatajsonvar.insert("encryptkeyhash", keyhash);
    metadatajsonvar.insert("type", type);
    metadatajsonvar.insert("currentid", currentid);

    QJsonObject obJct =QJsonObject::fromVariantMap(metadatajsonvar); //QVariantMap转QJsonObject
    QJsonDocument jsonDoc(obJct);//QJsonObject转QJsonDocument
    QByteArray json=jsonDoc.toJson();//QJsonDocument转QByteArray
    QString messagejsonstr(json);//QByteArray 转QString

    metadata = messagejsonstr;
    qDebug()<<"metadata ="<< metadata;
    qDebug()<<"数据元信息生成完成 ";

}


QString Metadata::calcfilehash(QString path, QString alg_method){
    FILE *from_fd = nullptr;
    char outcome[65] = "\0";
    int i = 0;
    //获取文件大小
    QFile localfile(path);
    const char* from_file_byte =nullptr;
    QByteArray ba = path.toLocal8Bit();
    from_file_byte = strdup(ba.data());
    unsigned char in[BUFFER_SIZE] = "\0";
    int bytes_read = 0;
    unsigned char out[33] = "\0";
    from_fd = fopen(from_file_byte, "rb");
    if (from_fd == nullptr) {
        return nullptr;
    }
    if (alg_method == "sha256") {
        sha256_context context;
        sha256_starts(&context);
        while (bytes_read = fread(in, sizeof(char), BUFFER_SIZE, from_fd)) {
            if ((bytes_read == -1) && (errno != EINTR)) {
                break;
            }
            else if (bytes_read == BUFFER_SIZE) {
                sha256_update(&context, in, bytes_read);
            }
            else if ((bytes_read < BUFFER_SIZE)) {
                sha256_update(&context, in, bytes_read);
            }
            else {
                sha256_update(&context, in, bytes_read);
            }
        }
        sha256_finish(&context , out);
        for (i = 0; i < 32; i++) {
            sprintf(outcome + 2 * i, "%02x", (unsigned char)out[i]);
        }
    }

    if (fclose(from_fd) == EOF) {
    }
    return QString(outcome);
}
QString Metadata::calcstrhash(QString input){
    char outcome[65] = "\0";//初始化变量
    unsigned char digest[32]="\0";//初始化变量
    unsigned char* inputbyte = (unsigned char*)(input.toUtf8().data());//QString类型转成(unsigned char*)类型
    int length = input.length();//获取字符串长度
    sha256(digest,inputbyte,length);//调用sha256算法直接计算输入的哈希值
    for (int i = 0; i < 32; i++) {
        sprintf(outcome + 2 * i, "%02x", (unsigned char)digest[i]);// 将哈希值以十六进制的形式输出到outcome中
    }
    return QString(outcome); //返回QString类型的计算结果
}


Metadata::~Metadata()
{
    delete ui;
}
