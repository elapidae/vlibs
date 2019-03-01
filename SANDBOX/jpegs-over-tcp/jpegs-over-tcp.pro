TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vzcm/vzcm.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/vtimer/vtimer.pri )
include( $$VLIBS_DIR/vthread/vthread.pri )

HEADERS += \
    cpp_types_basler/ZcmCameraBaslerJpegFrame.hpp

