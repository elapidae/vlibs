#-------------------------------------------------
#
# Project created by QtCreator 2018-12-18T17:48:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial_deploy
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
        mainwindow.cpp \
    qtserialport/src/serialport/qserialport.cpp \
    qtserialport/src/serialport/qserialportinfo_unix.cpp \
    qtserialport/src/serialport/qserialport_unix.cpp

HEADERS += \
        mainwindow.h \
    qtserialport/src/serialport/qserialport.h \
    qtserialport/src/serialport/qserialportglobal.h \
    qtserialport/src/serialport/qserialportinfo.h \
    qtserialport/src/serialport/qserialportinfo_p.h \
    qtserialport/src/serialport/qserialport_p.h

FORMS += \
        mainwindow.ui


INCLUDEPATH += $$PWD/../serial_deploy/qtserialport/src/

VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vserialport/vserialport.pri )

#DEFINES += -O7

#include( $$VLIBS_DIR/vlog/vlog_qt.pri )
#include( $$VLIBS_DIR/vposix/vposix.pri )
#include( $$VLIBS_DIR/vapplication/vapplication.pri )
##include( $$VLIBS_DIR/vserialsocket/vserialsocket.pri )
#include( $$VLIBS_DIR/vsignal/vsignal.pri )
#include( $$VLIBS_DIR/vstring/vstring.pri )
