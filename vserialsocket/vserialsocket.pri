#========================================================================================
# vserialsocket.pri
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
isEmpty(qi_vserialsocket) {
    qi_vserialsocket = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vserialsocket appended ===")

    isEmpty(VLIBS_DIR): error("vserialsocket: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vserialsocket

    
    HEADERS     += $$VLIBS_DIR/vserialsocket/vserialportoptions.h 
    HEADERS     += $$VLIBS_DIR/vserialsocket/vserialsocket.h 
    HEADERS     += $$VLIBS_DIR/vserialsocket/vserialport.h 
    
    SOURCES     += $$VLIBS_DIR/vserialsocket/vserialport.cpp 
    SOURCES     += $$VLIBS_DIR/vserialsocket/vserialportoptions.cpp 
    SOURCES     += $$VLIBS_DIR/vserialsocket/vserialsocket.cpp 
}
# vserialsocket.pri
#========================================================================================
