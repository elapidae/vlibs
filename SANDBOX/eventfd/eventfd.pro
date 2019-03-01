TEMPLATE = app
CONFIG += console
#CONFIG += c++11
#CONFIG -= app_bundle
#CONFIG -= qt



SOURCES += \
        main.cpp

VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vlog/vlog.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/vgeometry/vgeometry.pri )





include( $$VLIBS_DIR/vthread/vthread.pri )
include( $$VLIBS_DIR/vapplication/vapplication.pri )
#include( $$VLIBS_DIR/vgio/core/vgio_core.pri )
include( $$VLIBS_DIR/vstd/vstd.pri )
include( $$VLIBS_DIR/vpoll/vpoll.pri )
include( $$VLIBS_DIR/vposix/vposix.pri )
