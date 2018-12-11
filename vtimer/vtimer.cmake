#========================================================================================
# vtimer.cmake
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

if ( NOT  VTIMER_INCLUDED )
    set ( VTIMER_INCLUDED TRUE )

    message( "Include vtimer..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vsignal/vsignal.cmake" )
    include( "${VLIBS_DIR}/vposix/vposix.cmake" )
    include( "${VLIBS_DIR}/vapplication/vapplication.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vtimer/" )

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vtimer/vtimer.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vtimer/vtimer.cpp") 

    message( "vtimer included" )

endif()
# vtimer.cmake
#========================================================================================
