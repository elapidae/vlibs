TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += ../cmake_example_vlog/main.cpp



VLIBS_DIR = $$PWD/../..

# этого будет достаточно для логгирования в консоль.
include($$VLIBS_DIR/vlog/vlog.pri)
#include($$VLIBS_DIR/vstring/vstring.pri)
#include($$VLIBS_DIR/vgio/error/error.pri)
#include($$VLIBS_DIR/vchrono/vchrono.pri)
include($$VLIBS_DIR/vgio/keyfile/keyfile.pri)
#include($$VLIBS_DIR/voutfile/voutfile.pri)
include($$VLIBS_DIR/vlog/vfilelog.pri)

#Nio_Dir = $$VLIBS_DIR/nio_wrap
#Vlibs_Dir = $$VLIBS_DIR
#include($$Nio_Dir/nio_wrap.pri)

