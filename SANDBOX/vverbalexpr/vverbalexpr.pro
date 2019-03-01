QT       += core gui widgets

TARGET = vverbalexpr
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    vverbalexpr.cpp

HEADERS += \
        mainwindow.h \
    vverbalexpr.h


VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vlog/vlog_qt.pri )
include( $$VLIBS_DIR/vstd/vstd.pri )

MAIN_DIR = $$PWD
include( $$VLIBS_DIR/vgit/vgit.pri )
