#========================================================================================
# vnetwork.pri
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
isEmpty(qi_vnetwork) {
    qi_vnetwork = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vnetwork appended ===")

    isEmpty(VLIBS_DIR): error("vnetwork: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vsignal/vsignal.pri )
    include( $$VLIBS_DIR/vstring/vstring.pri )
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vposix/vposix.pri )
    include( $$VLIBS_DIR/vapplication/vapplication.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vnetwork

    
    HEADERS     += $$VLIBS_DIR/vnetwork/vtcpsocket.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vudpsocket.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vtcpserver.h 
    HEADERS     += $$VLIBS_DIR/vnetwork/vipaddress.h 
    
    SOURCES     += $$VLIBS_DIR/vnetwork/vtcpserver.cpp
    SOURCES     += $$VLIBS_DIR/vnetwork/vudpsocket.cpp 
    SOURCES     += $$VLIBS_DIR/vnetwork/vtcpsocket.cpp 
    SOURCES     += $$VLIBS_DIR/vnetwork/vipaddress.cpp 
}
# vnetwork.pri
#========================================================================================
