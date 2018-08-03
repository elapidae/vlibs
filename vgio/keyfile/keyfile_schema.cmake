#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------


#========================================================================================
if ( NOT  VGIO_KEYFILE_SCHEMA_INCLUDED )
    set ( VGIO_KEYFILE_SCHEMA_INCLUDED TRUE )
    message( "about vgio keyfile schema..." )

    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vgio/keyfile/keyfile.cmake" )


    FILE( GLOB HEADERS_vgio_keyfile_schema "${VGIO_DIR}/keyfile/vgio_keyfile_schema.h")
    FILE( GLOB SOURCES_vgio_keyfile_schema "${VGIO_DIR}/keyfile/vgio_keyfile_schema.cpp")

    set ( V_HEADERS ${V_HEADERS} ${HEADERS_vgio_keyfile_schema} )
    set ( V_SOURCES ${V_SOURCES} ${SOURCES_vgio_keyfile_schema} )


    message( "vgio keyfile schema included." )
endif()
#========================================================================================
