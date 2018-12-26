#========================================================================================
# vwatchdog.cmake
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

if ( NOT  VWATCHDOG_INCLUDED )
    set ( VWATCHDOG_INCLUDED TRUE )

    message( "Include vwatchdog..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vtimer/vtimer.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vwatchdog/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vwatchdog/vwatchdog.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vwatchdog/vwatchdog.cpp") 

    message( "vwatchdog included" )

endif()
# vwatchdog.cmake
#========================================================================================
