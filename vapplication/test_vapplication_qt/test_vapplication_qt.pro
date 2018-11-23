TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread
LIBS += -pthread

LIBS += -lgtest

SOURCES += run_test.cpp

VLIBS_DIR = $$PWD/../..
include( $$VLIBS_DIR/vapplication/vapplication.pri )
include( $$VLIBS_DIR/qt_pretty_build/qt_pretty_build_for_tests.pri )

#message($$TARGET)
#error($$QMAKE_PROJECT_NAME)
