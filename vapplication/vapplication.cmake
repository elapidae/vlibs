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
    include( "${VLIBS_DIR}/vstd/vstd.cmake" )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vpoll/vpoll_fds.h"   )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vpoll/vpoll_fds.cpp" )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vpoll/vpoll_queue.h"   )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vpoll/vpoll_queue.cpp" )

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vpoll/vpoll_queue_iface.h"   )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vapplication/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vapplication.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vapplication.cpp") 

    message( "vapplication included" )

endif()
# vapplication.cmake
#========================================================================================
