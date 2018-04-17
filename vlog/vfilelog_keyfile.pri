

isEmpty(qi_vfilelog_keyfile) {
    qi_vfilelog_keyfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfilelog_keyfile appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")
    include($$VLibs_Dir/vlog/vfilelog.pri)

    isEmpty(Nio_Dir): error("Need Nio_Dir correct path.")
    include($$Nio_Dir/nio_wrap.pri)


    HEADERS     += $$VLibs_Dir/vlog/vfilelog_keyfile.h
    SOURCES     += $$VLibs_Dir/vlog/vfilelog_keyfile.cpp
}
