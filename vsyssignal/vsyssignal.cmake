#========================================================================================
# vsyssignal.cmake
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

if ( NOT  VSYSSIGNAL_INCLUDED )
    set ( VSYSSIGNAL_INCLUDED TRUE )

    message( "Include vsyssignal..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vsyssignal/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vsyssignal/vsyssignal.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vsyssignal/vsyssignal.cpp") 

    message( "vsyssignal included" )

endif()
# vsyssignal.cmake
#========================================================================================
