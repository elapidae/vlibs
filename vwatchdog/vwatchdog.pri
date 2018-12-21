#========================================================================================
# vwatchdog.pri
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
isEmpty(qi_vwatchdog) {
    qi_vwatchdog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vwatchdog appended ===")

    isEmpty(VLIBS_DIR): error("vwatchdog: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vtimer/vtimer.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vwatchdog

    
    HEADERS     += $$VLIBS_DIR/vwatchdog/vwatchdog.h 
    
    SOURCES     += $$VLIBS_DIR/vwatchdog/vwatchdog.cpp 
}
# vwatchdog.pri
#========================================================================================
