#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T10:23:16
#
#-------------------------------------------------

QT       += core gui multimediawidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rtsp-over-qtmultimedia
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
    four_images.cpp \
    vmacroses.cpp

HEADERS += \
    four_images.h \
    vmacroses.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lpulse-mainloop-glib
LIBS += -lpulse

VLIBS_DIR = $$PWD/../../vlibs
include( $$VLIBS_DIR/vlog/vlog_qt.pri )
include( $$VLIBS_DIR/vzcm/vzcm.pri )
include( $$VLIBS_DIR/qt_vinvoke/qt_vinvoke.pri )
include( $$VLIBS_DIR/vnetwork/vnetwork.pri )
include( $$VLIBS_DIR/vopencv/vopencv.pri )
include( $$VLIBS_DIR/vimagewidget/vimagewidget.pri )
include( $$VLIBS_DIR/vjpeg/vjpeg.pri )
#include( $$VLIBS_DIR/vserialsocket/vserialsocket.pri )
#include( $$VLIBS_DIR/vserialsocket/vserialsocket.pri )
#include( $$VLIBS_DIR/hdlc_parser/hdlc_parser.pri )

#QT += avwidgets



INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5
LIBS += -lQt5AV -lQt5AVWidgets
