#========================================================================================
# vserialsocket.cmake
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

if ( NOT  VSERIALSOCKET_INCLUDED )
    set ( VSERIALSOCKET_INCLUDED TRUE )

    message( "Include vserialsocket..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vserialsocket/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vserialsocket/vserialportoptions.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vserialsocket/vserialsocket.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vserialsocket/vserialport.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vserialsocket/vserialport.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vserialsocket/vserialportoptions.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vserialsocket/vserialsocket.cpp") 

    message( "vserialsocket included" )

endif()
# vserialsocket.cmake
#========================================================================================
