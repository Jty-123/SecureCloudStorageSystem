#ifndef SONOBJECT_H
#define SONOBJECT_H

#include <QObject>
#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

class SonObject : public QObject
{
    Q_OBJECT
public:
    explicit SonObject(QObject *parent = nullptr);
    void DoSetup(QThread &cThread );
signals:
    void sendsignal(QString);
public slots:
    void operation();
};

#endif // SONOBJECT_H
