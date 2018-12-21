#========================================================================================
# vstd.pri
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
isEmpty(qi_vstd) {
    qi_vstd = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vstd appended ===")

    isEmpty(VLIBS_DIR): error("vstd: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vstd

    
    HEADERS     += $$VLIBS_DIR/vstd/vstd_atomic_queue.h 
    HEADERS     += $$VLIBS_DIR/vstd/vstd_atomic_map.h 
    
    SOURCES     += $$VLIBS_DIR/vstd/vstd_atomic_queue.cpp 
}
# vstd.pri
#========================================================================================
