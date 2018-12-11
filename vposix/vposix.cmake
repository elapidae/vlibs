#========================================================================================
# vposix.cmake
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

if ( NOT  VPOSIX_INCLUDED )
    set ( VPOSIX_INCLUDED TRUE )

    message( "Include vposix..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vposix/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_core.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_files.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_network.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_signal.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_eventfd.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_epoll.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_timerfd.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_network_ip.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_alloca.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_network.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_timerfd.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_epoll.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_signal.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_network_ip.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_alloca.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_eventfd.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_files.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_core.cpp") 

    message( "vposix included" )

endif()
# vposix.cmake
#========================================================================================
