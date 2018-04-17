

isEmpty(qi_zcm_image) {
    qi_zcm_image = 1;
    isEmpty(qi_not_print_pri_messages): message("=== zcm_image appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")
    include($$VLibs_Dir/vimage/vimage.pri)
    include($$VLibs_Dir/vzcm/vzcm.pri)

    HEADERS += $$VLibs_Dir/vimage/z_image.h
    #HEADERS += $$VLibs_Dir/vimage/ZCM_Image.h
    SOURCES += $$VLibs_Dir/vimage/z_image.cpp

    vzcm_image_pre_target.target = vzcm_image
    vzcm_image_pre_target.commands = \
        cd $$system_path($$PWD/zcm_prototypes) &&   \
        if [ ! -f ../ZCM_Image.hpp ]; then          \
        zcm-gen -x zcm_image.zcm --cpp-hpath ..; fi


    vzcm_image_pre_target.CONFIG = phony
    QMAKE_EXTRA_TARGETS +=   vzcm_image_pre_target
    PRE_TARGETDEPS      += $$vzcm_image_pre_target.target
    first.depends       += $$vzcm_image_pre_target.target
}

