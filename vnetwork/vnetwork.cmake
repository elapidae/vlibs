#========================================================================================
# vnetwork.cmake
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

if ( NOT  VNETWORK_INCLUDED )
    set ( VNETWORK_INCLUDED TRUE )

    message( "Include vnetwork..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vnetwork/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vnetwork/vtcpsocket.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vnetwork/vudpsocket.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vnetwork/vtcpserver.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vnetwork/vipaddress.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vnetwork/vtcpserver.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vnetwork/vudpsocket.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vnetwork/vtcpsocket.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vnetwork/vipaddress.cpp") 

    message( "vnetwork included" )

endif()
# vnetwork.cmake
#========================================================================================
