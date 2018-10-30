#========================================================================================
# vrandom.pri
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
isEmpty(qi_vrandom) {
    qi_vrandom = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vrandom appended ===")

    isEmpty(VLIBS_DIR): error("vrandom: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vrandom

    
    HEADERS     += $$VLIBS_DIR/vrandom/vrandom.h 
    
    SOURCES     += $$VLIBS_DIR/vrandom/vrandom.cpp 
}
# vrandom.pri
#========================================================================================
