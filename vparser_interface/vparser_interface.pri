
isEmpty(qi_vparser_interface) {
    qi_vparser_interface = 1;
    
    isEmpty(qi_not_print_pri_messages): message("=== vparser_interface appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vparser_interface

    HEADERS     += $$VLibs_Dir/vparser_interface/vparser_interface.h
    SOURCES     += $$VLibs_Dir/vparser_interface/vparser_interface.cpp
}

