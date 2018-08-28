#========================================================================================
# vchrono.pri
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
isEmpty(qi_vchrono) {
    qi_vchrono = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vchrono appended ===")

    isEmpty(VLIBS_DIR): error("vchrono: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vcat/vcat.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vchrono

    
    HEADERS     += $$VLIBS_DIR/vchrono/vtimepoint.h 
    HEADERS     += $$VLIBS_DIR/vchrono/vchrono_weeks.h 
    
    SOURCES     += $$VLIBS_DIR/vchrono/vtimepoint.cpp 
}
# vchrono.pri
#========================================================================================
