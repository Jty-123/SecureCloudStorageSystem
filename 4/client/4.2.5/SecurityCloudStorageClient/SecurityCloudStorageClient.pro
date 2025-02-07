#-------------------------------------------------
#
# Project created by QtCreator 2019-11-08T18:29:45
#
#-------------------------------------------------


QT       += core gui network widgets

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
        global.cpp \
        main.cpp \
        opensource/aes_cbc.c \
        opensource/aes_core.c \
        opensource/base64_enc.c \
        opensource/sha256.c \
        securitycloudstorageclientwidget.cpp \
        transformentity/uploadfileentity.cpp \
        transformentity/uploadoperation.cpp \
        transformlistform/uploadlistform.cpp

HEADERS += \
        global.h \
        inc/aes_cbc.h \
        inc/base64_enc.h \
        inc/sha256.h \
        lib/include/cipherinterface.h \
        securitycloudstorageclientwidget.h \
        transformentity/uploadfileentity.h \
        transformentity/uploadoperation.h \
        transformlistform/uploadlistform.h


FORMS += \
        securitycloudstorageclientwidget.ui \
        transformlistform/uploadlistform.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resource.qrc\


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:unix: LIBS += -L$$PWD/lib/ -lCipherIndexLib

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:unix: LIBS += -L$$PWD/lib/ -lYunLock

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    dict/README.md \
    dict/hmm_model.utf8 \
    dict/idf.utf8 \
    dict/jieba.dict.utf8 \
    dict/stop_words.utf8 \
    dict/user.dict.utf8 \
    lib/dict/README.md \
    lib/dict/hmm_model.utf8 \
    lib/dict/idf.utf8 \
    lib/dict/jieba.dict.utf8 \
    lib/dict/stop_words.utf8 \
    lib/dict/user.dict.utf8
