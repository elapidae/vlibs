TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp


VLibs_Dir = $$PWD/../..
include( $$VLibs_Dir/vbitmessage/vbitmessage.pri )
include( $$VLibs_Dir/vlog/vlog.pri )
