
isEmpty(qi_vapp_args_parser) {
    qi_vapp_args_parser = 1;
    isEmpty(qi_not_print_pri_messages): message("=== args parser appended ===")


    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    INCLUDEPATH += $$VLibs_Dir/vapp_args_parser

    HEADERS     += $$VLibs_Dir/vapp_args_parser/vapp_args_parser.h
    SOURCES     += $$VLibs_Dir/vapp_args_parser/vapp_args_parser.cpp
}

