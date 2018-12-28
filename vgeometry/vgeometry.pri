#========================================================================================
# vgeometry.pri
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
isEmpty(qi_vgeometry) {
    qi_vgeometry = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgeometry appended ===")

    isEmpty(VLIBS_DIR): error("vgeometry: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vgeometry

    
    HEADERS     += $$VLIBS_DIR/vgeometry/vline.h 
    HEADERS     += $$VLIBS_DIR/vgeometry/vtransformation.h 
    HEADERS     += $$VLIBS_DIR/vgeometry/vpoints.h 
    HEADERS     += $$VLIBS_DIR/vgeometry/vinterval.h 
    
    SOURCES     += $$VLIBS_DIR/vgeometry/vtransformation.cpp 
}
# vgeometry.pri
#========================================================================================
