#========================================================================================
# vstring.pri
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
isEmpty(qi_vstring) {
    qi_vstring = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vstring appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vstring

    
    HEADERS     += $$VLIBS_DIR/vstring/vbufferforwardreader.h 
    HEADERS     += $$VLIBS_DIR/vstring/vstring.h 
    
    SOURCES     += $$VLIBS_DIR/vstring/vstring.cpp 
    SOURCES     += $$VLIBS_DIR/vstring/vbufferforwardreader.cpp 
}
# vstring.pri
#========================================================================================
