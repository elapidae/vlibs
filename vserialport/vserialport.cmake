#========================================================================================
# vserialport.cmake
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

if ( NOT  VSERIALPORT_INCLUDED )
    set ( VSERIALPORT_INCLUDED TRUE )

    message( "Include vserialport..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vserialport/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vserialport/vserialport.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vserialport/vserialport.cpp") 

    message( "vserialport included" )

endif()
# vserialport.cmake
#========================================================================================
