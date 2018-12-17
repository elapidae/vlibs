#========================================================================================
# hdlc_parser.pri
#
#
# Этот файл сгенерирован автоматически.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================
isEmpty(qi_hdlc_parser) {
    qi_hdlc_parser = 1;
    isEmpty(qi_not_print_pri_messages): message("=== hdlc_parser appended ===")

    isEmpty(VLIBS_DIR): error("hdlc_parser: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/hdlc_parser

    
    HEADERS     += $$VLIBS_DIR/hdlc_parser/hdlc_parser.h 
    
    SOURCES     += $$VLIBS_DIR/hdlc_parser/hdlc_parser.cpp 
}
# hdlc_parser.pri
#========================================================================================
