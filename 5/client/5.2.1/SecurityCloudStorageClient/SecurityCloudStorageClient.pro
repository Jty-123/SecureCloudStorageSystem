#-------------------------------------------------
#
# Project created by QtCreator 2019-11-08T18:29:45
#
#-------------------------------------------------


QT += core gui network widgets

QT += testlib
CONFIG += testcase
#CONFIG += qt console warn_on depend_includepath testcase

#QT += testlib
#QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecurityCloudStorageClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#CONFIG += testcase
CONFIG += c++11
#CONFIG += qt warn_on depend_includepath testcase


SOURCES += \
    FileShare/cancelshare.cpp \
    FileShare/datashareentity.cpp \
    FileShare/filesharewidget.cpp \
    FileShare/getsharedlist.cpp \
    FileShare/getsharelist.cpp \
    FileStructureList/filestructurelist.cpp \
    FolderStructureList/folderstructurelist.cpp \
    LocalLog/locallogdialog.cpp \
    Login/loginwidget.cpp \
    LocalLog/seccloudlog.cpp \
    OnlineUpdate/onlineupdatedialog.cpp \
    OnlineUpdate/onlineupdateoperation.cpp \
    SearchResult/searchoperation.cpp \
    Test/functiontest.cpp \
    Test/testlogingui.cpp \
    entities/filemetadata.cpp \
    entities/localtreewidgetitem.cpp \
    global.cpp \
        main.cpp \
    opensource/aes_cbc.c \
    opensource/aes_core.c \
    opensource/base64_dec.c \
    opensource/base64_enc.c \
    opensource/des.c \
    opensource/hmac_md5.c \
    opensource/hmac_sha1.c \
    opensource/hmac_sha256.c \
    opensource/md5.c \
    opensource/rijndeal.c \
    opensource/sha1.c \
    opensource/sha256.c \
        operationwidget.cpp \
        securitycloudstorageclientwidget.cpp \
    SearchResult/searchresultwidget.cpp \
    local_lineedit/local_lineedit.cpp \
    transformentity/downloadfileentity.cpp \
    transformentity/downloadoperation.cpp \
    transformentity/uploadfileentity.cpp \
    transformentity/uploadoperation.cpp \
    transformlistform/downloadlistform.cpp \
    transformlistform/transformlistform.cpp \
    transformlistform/uploadlistform.cpp \
    tst_testname.cpp

HEADERS += \
    FileShare/cancelshare.h \
    FileShare/datashareentity.h \
    FileShare/filesharewidget.h \
    FileShare/getsharedlist.h \
    FileShare/getsharelist.h \
    FileStructureList/filestructurelist.h \
    FolderStructureList/folderstructurelist.h \
    LocalLog/locallogdialog.h \
    Login/loginwidget.h \
    LocalLog/seccloudlog.h \
    OnlineUpdate/onlineupdatedialog.h \
    OnlineUpdate/onlineupdateoperation.h \
    SearchResult/searchoperation.h \
    Test/functiontest.h \
    Test/testlogingui.h \
    entities/filemetadata.h \
    entities/localtreewidgetitem.h \
    lib/include/cipherinterface.h \
    global.h \
    inc/aes_cbc.h \
    inc/alg_err.h \
    inc/base64_dec.h \
    inc/base64_enc.h \
    inc/crypt.h \
    inc/des.h \
    inc/hmac_md5.h \
    inc/hmac_sha1.h \
    inc/hmac_sha256.h \
    inc/md5.h \
    inc/rijndael.h \
    inc/sha1.h \
    inc/sha256.h \
        operationwidget.h \
        securitycloudstorageclientwidget.h \
    SearchResult/searchresultwidget.h \
    local_lineedit/local_lineedit.h \
    transformentity/downloadfileentity.h \
    transformentity/downloadoperation.h \
    transformentity/uploadfileentity.h \
    transformentity/uploadoperation.h \
    transformlistform/downloadlistform.h \
    transformlistform/transformlistform.h \
    transformlistform/uploadlistform.h

FORMS += \
    FileShare/filesharewidget.ui \
    LocalLog/locallogdialog.ui \
    Login/loginwidget.ui \
    OnlineUpdate/onlineupdatedialog.ui \
        operationwidget.ui \
        securitycloudstorageclientwidget.ui \
    SearchResult/searchresultwidget.ui \
    transformlistform/downloadlistform.ui \
    transformlistform/transformlistform.ui \
    transformlistform/uploadlistform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resource.qrc\

RC_FILE +=\
    admin.rc


INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include
INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:unix: LIBS += -L$$PWD/lib/ -lCipherIndexLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:unix: LIBS += -L$$PWD/lib/ -lYunLock





