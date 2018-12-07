#========================================================================================
# vtimer.pri
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
isEmpty(qi_vtimer) {
    qi_vtimer = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vtimer appended ===")

    isEmpty(VLIBS_DIR): error("vtimer: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vposix/vposix.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vtimer

    
    HEADERS     += $$VLIBS_DIR/vtimer/vtimer.h 
    
    SOURCES     += $$VLIBS_DIR/vtimer/vtimer.cpp 
}
# vtimer.pri
#========================================================================================
