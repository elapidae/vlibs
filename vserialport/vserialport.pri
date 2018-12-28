#========================================================================================
# vserialport.pri
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
isEmpty(qi_vserialport) {
    qi_vserialport = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vserialport appended ===")

    isEmpty(VLIBS_DIR): error("vserialport: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vsignal/vsignal.pri )
    include( $$VLIBS_DIR/vstring/vstring.pri )
    include( $$VLIBS_DIR/vapplication/vapplication.pri )

    OTHER_FILES += $$VLIBS_DIR/vserialport/vserialport.cmake
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vserialport

    
    HEADERS     += $$VLIBS_DIR/vserialport/vserialport.h 
    
    SOURCES     += $$VLIBS_DIR/vserialport/vserialport.cpp 
}
# vserialport.pri
#========================================================================================
