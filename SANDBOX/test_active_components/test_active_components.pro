TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vapplication/vapplication.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/vtimer/vtimer.pri )


