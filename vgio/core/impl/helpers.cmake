#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------

if ( NOT  VGIO_HELPERS_INCLUDED )
    set ( VGIO_HELPERS_INCLUDED TRUE )
    message( "about vgio helpers ..." )

    include( "${VLIBS_DIR}/vgio/core/core.cmake" )

    FILE( GLOB HEADERS_vgio_cast_help "${VGIO_DIR}/core/impl/vgio_casting_helper.h"   )
    #FILE( GLOB SOURCES_vgio_cast_help "${VGIO_DIR}/core/vgio_casting_helper.cpp" )

    FILE( GLOB HEADERS_vgio_conv_help "${VGIO_DIR}/core/impl/vgio_converting_helper.h"  )
    FILE( GLOB SOURCES_vgio_conv_help "${VGIO_DIR}/core/impl/vgio_converting_helper.cpp")

    include_directories( "${VGIO_DIR}/core" )

    set ( V_HEADERS ${V_HEADERS} ${HEADERS_vgio_cast_help} )
    set ( V_SOURCES ${V_SOURCES} ${SOURCES_vgio_cast_help} )

    set ( V_HEADERS ${V_HEADERS} ${HEADERS_vgio_conv_help} )
    set ( V_SOURCES ${V_SOURCES} ${SOURCES_vgio_conv_help} )

    message( "vgio helpers included." )
endif()



