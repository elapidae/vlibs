#========================================================================================
# vstd.cmake
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

if ( NOT  VSTD_INCLUDED )
    set ( VSTD_INCLUDED TRUE )

    message( "Include vstd..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vstd/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vstd/vstd_atomic_queue.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vstd/vstd_atomic_map.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vstd/vstd_atomic_queue.cpp") 

    message( "vstd included" )

endif()
# vstd.cmake
#========================================================================================
