#========================================================================================
#   UPD 2018-08-28      by Elapidae
#   Ручной сборки, пока что, некоторые мысли по автосборке в зачаточном состоянии,
#   ниже основного включения хранятся замороженные попытки автосборок.
#========================================================================================


#========================================================================================
isEmpty(qi_vzcm) {
    qi_vzcm = 1;

    LIBS += -lzcm -L/usr/local/lib

    include( $$VLIBS_DIR/vsignal/vsignal.pri )

    INCLUDEPATH += $$VLIBS_DIR/vzcm
    HEADERS     += $$VLIBS_DIR/vzcm/vzcm_subscriber.h
}
#========================================================================================



#========================================================================================
#   FREEZED
#========================================================================================

#include <zcm/zcm-cpp.hpp>


#    vzcm_image_pre_target.target = vzcm_image
#    vzcm_image_pre_target.commands = \
#        cd $$system_path($$PWD/zcm_prototypes) &&   \
#        if [ ! -f ../ZCM_Image.hpp ]; then          \
#        zcm-gen -x zcm_image.zcm --cpp-hpath ..;    \
#        fi


#    vzcm_image_pre_target.CONFIG = phony
#    QMAKE_EXTRA_TARGETS +=   vzcm_image_pre_target
#    PRE_TARGETDEPS      += $$vzcm_image_pre_target.target
#    first.depends       += $$vzcm_image_pre_target.target
#========================================================================================

