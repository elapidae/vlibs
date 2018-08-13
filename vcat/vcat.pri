#========================================================================================
# vcat.pri
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
isEmpty(qi_vcat) {
    qi_vcat = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vcat appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vcat

    
    HEADERS     += $$VLIBS_DIR/vcat/vcat_containers.h 
    HEADERS     += $$VLIBS_DIR/vcat/vcat.h 
    HEADERS     += $$VLIBS_DIR/vcat/_vcat_iface.h 
    
    SOURCES     += $$VLIBS_DIR/vcat/vcat.cpp 
}
# vcat.pri
#========================================================================================
