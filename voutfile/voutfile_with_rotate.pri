#========================================================================================
# voutfile.pri
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
isEmpty(qi_voutfile) {
    qi_voutfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== voutfile appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/voutfile

    
    HEADERS     += $$VLIBS_DIR/voutfile/voutfile.h 
    HEADERS     += $$VLIBS_DIR/voutfile/voutfile_withrotate.h 
    
    SOURCES     += $$VLIBS_DIR/voutfile/voutfile_withrotate.cpp 
    SOURCES     += $$VLIBS_DIR/voutfile/voutfile.cpp 
}
# voutfile.pri
#========================================================================================
