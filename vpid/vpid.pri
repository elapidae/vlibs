

isEmpty(qi_vpid) {
    qi_vpid = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpid appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    include($$VLibs_Dir/vlog/vlog.pri)
    include($$VLibs_Dir/voutfile/voutfile.pri)
    include($$VLibs_Dir/vdir/vdir.pri)

    INCLUDEPATH += $$VLibs_Dir/vpid

    HEADERS     += $$VLibs_Dir/vpid/vpid_saver.h
    SOURCES     += $$VLibs_Dir/vpid/vpid_saver.cpp
}


