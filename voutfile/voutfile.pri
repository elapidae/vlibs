

isEmpty(qi_voutfile) {
    qi_voutfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== voutfile appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/voutfile

    HEADERS     += $$VLibs_Dir/voutfile/voutfile.h
    SOURCES     += $$VLibs_Dir/voutfile/voutfile.cpp
    
    HEADERS     += $$VLibs_Dir/voutfile/voutfile_withrotate.h
    SOURCES     += $$VLibs_Dir/voutfile/voutfile_withrotate.cpp
}
