TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt console

#SOURCES += \
#        main.cpp


VLIBS_DIR = $$PWD/../../vlibs
#include( $$VLIBS_DIR/vlog/vlog.pri )
include( $$VLIBS_DIR/vlog/vfilelog.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )

#SOURCES += $$files($$PWD/*.cpp)
#error($$SOURCES)
