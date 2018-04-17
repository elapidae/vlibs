

isEmpty(qi_vzcm) {
    qi_vzcm = 1;

#include <zcm/zcm-cpp.hpp>

    LIBS += -lzcm -L/usr/local/lib
}

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
