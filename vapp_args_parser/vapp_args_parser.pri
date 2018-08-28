#========================================================================================
#   2018-08-28      by Elapidae
#
#   Этот файл устарел, его задача планируется на перенос в класс VApplication.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vapp_args_parser) {
    qi_vapp_args_parser = 1;
    isEmpty(qi_not_print_pri_messages): message("=== args parser appended ===")


    isEmpty(VLIBS_DIR): error("vapp_args_parser: Need VLIBS_DIR correct path.")

    INCLUDEPATH += $$VLIBS_DIR/vapp_args_parser

    HEADERS     += $$VLIBS_DIR/vapp_args_parser/vapp_args_parser.h
    SOURCES     += $$VLIBS_DIR/vapp_args_parser/vapp_args_parser.cpp
}
#========================================================================================

