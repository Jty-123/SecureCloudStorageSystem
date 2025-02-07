#-------------------------------------------------
#
# Project created by QtCreator 2020-03-03T22:14:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metadata
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        metadata.cpp \
        opensource/sha256.c

HEADERS += \
        inc/sha256.h \
        lib/include/cipherinterface.h \
        metadata.h

FORMS += \
        metadata.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lYunLock
else:unix: LIBS += -L$$PWD/lib/ -lYunLock

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lCipherIndexLib
else:unix: LIBS += -L$$PWD/lib/ -lCipherIndexLib

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
