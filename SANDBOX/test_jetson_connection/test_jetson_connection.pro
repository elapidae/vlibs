#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T10:53:07
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_jetson_connection
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    cpp_types_basler/ZcmCameraBaslerFrame.hpp \
    cpp_types_basler/ZcmCameraBaslerImagePresentation.hpp \
    cpp_types_basler/ZcmCameraBaslerInformation.hpp \
    cpp_types_basler/ZcmCameraBaslerJpegFrame.hpp \
    cpp_types_basler/ZcmCameraCalibratingParams.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vlog/vlog_qt.pri )
include( $$VLIBS_DIR/vstring/vstring.pri )
include( $$VLIBS_DIR/vimagewidget/vimagewidget.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/vgstreamer/vgstreamer.pri )
