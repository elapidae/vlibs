TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vlog/vlog.pri )
