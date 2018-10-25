#========================================================================================
# error.pri
#
#   NB! Отредактировано руками!
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vgio_error) {
    qi_vgio_error = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgio_error appended ===")

    isEmpty(VLIBS_DIR): error("vgio_error: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vgio/error
    
    HEADERS     += $$VLIBS_DIR/vgio/error/vgio_error.h
    SOURCES     += $$VLIBS_DIR/vgio/error/vgio_error.cpp
}
# error.pri
#========================================================================================
