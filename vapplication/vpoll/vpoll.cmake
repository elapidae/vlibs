#========================================================================================
# vpoll.cmake
#   Manual edited.
#========================================================================================


#========================================================================================

if ( NOT  VPOLL_INCLUDED )
    set ( VPOLL_INCLUDED TRUE )

    message( "Include vpoll..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vstd/vstd.cmake" )
    #>>> Stop your code here ------------------------------------------------------------
    
    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapplication/vpoll/vpoll.h" )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapplication/vpoll/vpoll.cpp" )

    message( "vpoll included" )

endif()
# vpoll.cmake
#========================================================================================
