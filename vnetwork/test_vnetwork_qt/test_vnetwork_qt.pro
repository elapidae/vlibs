TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread
LIBS += -pthread

LIBS += -lgtest

SOURCES += run_test.cpp

VLIBS_DIR = $$PWD/../..
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/qt_pretty_build/qt_pretty_build_for_tests.pri )
include( $$VLIBS_DIR/vsyssignal/vsyssignal.pri )
include( $$VLIBS_DIR/vtimer/vtimer.pri )
