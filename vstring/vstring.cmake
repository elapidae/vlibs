#========================================================================================
# vstring.cmake
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

if ( NOT  VSTRING_INCLUDED )
    set ( VSTRING_INCLUDED TRUE )

    message( "Include vstring..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/c++11/c++11.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vstring/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vstring/vstring.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vstring/vstring.cpp") 

    message( "vstring included" )

endif()
# vstring.cmake
#========================================================================================
