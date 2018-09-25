#========================================================================================
# vapplication.pri
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
isEmpty(qi_vapplication) {
    qi_vapplication = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vapplication appended ===")

    isEmpty(VLIBS_DIR): error("vapplication: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #include( $$VLIBS_DIR/vstring/vstring.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vfile/vfile.pri )
    OTHER_FILES += $$VLIBS_DIR/vapplication/README
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vapplication

    
    HEADERS     += $$VLIBS_DIR/vapplication/vapplication.h 
    
    SOURCES     += $$VLIBS_DIR/vapplication/vapplication.cpp 
}
# vapplication.pri
#========================================================================================
