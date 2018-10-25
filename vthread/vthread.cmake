#========================================================================================
# vthread.cmake
#
#   Manual tuned.
#========================================================================================


#========================================================================================

if ( NOT  VTHREAD_INCLUDED )
    set ( VTHREAD_INCLUDED TRUE )

    message( "Include vthread..." )

    #<<< Start your code here -----------------------------------------------------------
    #add_definitions( -DVTHREAD_USE_PTHREAD )
    link_libraries( pthread )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vthread/")

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vsemaphore/vsemaphore.h")
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vthread/vsemaphore/vsemaphore.cpp")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vthread.h") 
    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vslot.h")
    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vapplication.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vsemaphorequeue.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vthread/vthreadqueue.h") 
    
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vthread/vapplication.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vthread/vthreadqueue.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vthread/vthread.cpp") 
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vthread/vslot.cpp")

    message( "vthread included" )

endif()
# vthread.cmake
#========================================================================================
