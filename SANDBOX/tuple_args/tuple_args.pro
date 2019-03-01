#-------------------------------------------------
#
# Project created by QtCreator 2018-10-01T13:14:59
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tuple_args
TEMPLATE = app

QMAKE_CXXFLAGS += -ftemplate-depth=100

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
#        mainwindow.cpp \
#    vztop_coder.cpp \
#    vztop_ztop.cpp \
#    vztop_buffer.cpp \
#    vztop_deploy.cpp \
#    vztop_encoder.cpp \
#    vztop_signature.cpp
  #  vztop_decoder.cpp
#    vserialize_serializable.cpp \
#    ishumi_serialize.cpp \
#    ishumi_impl_signature.cpp \
#    ishumi_impl_readbuffer.cpp \
#    ishumi_impl_writebuffer.cpp \
#    ishumi_impl_encoder.cpp \
#    ishumi_impl_decoder.cpp \
#    vtype_traits.cpp \
   serialization/serialization_type_traits.cpp \
#    ii_udp_splitter.cpp \
#    ii_udp_packets_unmerge.cpp \
#    ii_udp_packets.cpp

HEADERS += \
#        mainwindow.h \
#    vztop_coder.h \
#    vztop_ztop.h \
#    vztop_deploy.h \
#    vztop_encoder.h \
#    vztop_signature.h \
#    vztop_decoder.h \
#    vztop_buffers.h \
#    vserialize_serializable.h \
#    ishumi_serialize.h \
#    ishumi_impl_signature.h \
#    ishumi_impl_readbuffer.h \
#    ishumi_impl_writebuffer.h \
#    ishumi_impl_encoder.h \
#    ishumi_impl_decoder.h \
#    vtype_traits.h \
    serialization/serialization_type_traits.h \
#    ii_serializable.h \
#    ii_udp_splitter.h \
#    ii_udp_packets_unmerge.h \
#    ii_udp_packets.h

#FORMS += \
#        mainwindow.ui

VLIBS_DIR = $$PWD/../../vlibs
#VLIBS_DIR = $$PWD/vlibs
include( $$VLIBS_DIR/vstring/vstring.pri )
include( $$VLIBS_DIR/vlog/vlog.pri )
include( $$VLIBS_DIR/vpoints/vpoints.pri )
include( $$VLIBS_DIR/vcrc/vcrc.pri )
include( $$VLIBS_DIR/vsignal/vsignal.pri )

LIBS += -lgtest
