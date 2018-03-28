
#========================================================================================
isEmpty(qi_vbitmessage) {
    qi_vbitmessage = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vbitmessage appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vbitmessage

    HEADERS     += $$VLibs_Dir/vbitmessage/voutbitmessage.h
    SOURCES     += $$VLibs_Dir/vbitmessage/voutbitmessage.cpp
}
#========================================================================================

