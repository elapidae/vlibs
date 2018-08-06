#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------

#========================================================================================
if ( NOT  VGIO_ERROR_INCLUDED )
    set ( VGIO_ERROR_INCLUDED TRUE )
    message( "about vgio error ..." )

    include( "${VLIBS_DIR}/vgio/core/core.cmake" )

    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )

    include_directories( "${VLIBS_DIR}/vgio/error" )

    FILE( GLOB HEADERS_vgio_error "${VGIO_DIR}/error/vgio_error.h"   )
    FILE( GLOB SOURCES_vgio_error "${VGIO_DIR}/error/vgio_error.cpp" )

    set ( V_HEADERS ${V_HEADERS} ${HEADERS_vgio_error} )
    set ( V_SOURCES ${V_SOURCES} ${SOURCES_vgio_error} )

    message( "vgio error included." )

endif()
#========================================================================================



