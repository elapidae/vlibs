TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp



VLibs_Dir = $$PWD/../..

# этого будет достаточно для логгирования в консоль.
#include($$VLibs_Dir/vlog/vlog.pri)

include($$VLibs_Dir/vlog/vfilelog.pri)
