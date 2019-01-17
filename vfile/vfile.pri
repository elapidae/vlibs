#========================================================================================
# vfile.pri
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
isEmpty(qi_vfile) {
    qi_vfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vfile appended ===")

    isEmpty(VLIBS_DIR): error("vfile: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vposix/vposix.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vfile

    
    HEADERS     += $$VLIBS_DIR/vfile/vfile.h 
    
    SOURCES     += $$VLIBS_DIR/vfile/vfile.cpp 
}
# vfile.pri
#========================================================================================
