#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------


#========================================================================================
if ( NOT  VGIO_KEYFILE_INCLUDED )
    set ( VGIO_KEYFILE_INCLUDED TRUE )
    message( "about vgio keyfile ..." )

    include( "${VLIBS_DIR}/vgio/error/error.cmake" )
    include( "${VLIBS_DIR}/vgio/core/impl/helpers.cmake" )

    include_directories( "${VLIBS_DIR}/vgio/keyfile" )

    FILE( GLOB HEADERS_vgio_keyfile "${VGIO_DIR}/keyfile/vgio_keyfile.h"   )
    FILE( GLOB SOURCES_vgio_keyfile "${VGIO_DIR}/keyfile/vgio_keyfile.cpp" )

    set ( V_HEADERS ${V_HEADERS} ${HEADERS_vgio_keyfile} )
    set ( V_SOURCES ${V_SOURCES} ${SOURCES_vgio_keyfile} )


    message( "vgio keyfile included." )
endif()
#========================================================================================
