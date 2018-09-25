#========================================================================================
# vposix.pri
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
isEmpty(qi_vposix) {
    qi_vposix = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vposix appended ===")

    isEmpty(VLIBS_DIR): error("vposix: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    OTHER_FILES += $$VLIBS_DIR/vposix/README
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vposix

    
    HEADERS     += $$VLIBS_DIR/vposix/vposix_errno.h 
    HEADERS     += $$VLIBS_DIR/vposix/vposix_files.h 
    
    SOURCES     += $$VLIBS_DIR/vposix/vposix_errno.cpp 
    SOURCES     += $$VLIBS_DIR/vposix/vposix_files.cpp 
}
# vposix.pri
#========================================================================================
