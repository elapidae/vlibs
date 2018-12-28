#========================================================================================
# vapplication.cmake
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

if ( NOT  VAPPLICATION_INCLUDED )
    set ( VAPPLICATION_INCLUDED TRUE )

    message( "Include vapplication..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vfile/vfile.cmake" )
    include( "${VLIBS_DIR}/vapplication/vpoll/vpoll.cmake" )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vinvoke/vinvoke_iface.h"  )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vinvoke/vinvokequeue.h"   )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vinvoke/vinvokequeue.cpp" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vapplication/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vapplication.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vapplication.cpp") 

    message( "vapplication included" )

endif()
# vapplication.cmake
#========================================================================================
