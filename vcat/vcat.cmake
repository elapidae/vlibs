

message( "Include vcat..." )

include_directories( "${VLIBS_PATH}/vcat/" )

FILE( GLOB HEADERS_Vcat "${VLIBS_PATH}/vcat/*.h"   )
FILE( GLOB SOURCES_Vcat "${VLIBS_PATH}/vcat/*.cpp" )

set ( V_HEADERS ${V_HEADERS} ${HEADERS_Vcat} )
set ( V_SOURCES ${V_SOURCES} ${SOURCES_Vcat} )

if( NOT CPP11_STANDARD_INCLUDED )
    add_definitions( -std=c++11 )
    set ( CPP11_STANDARD_INCLUDED TRUE )
endif()

message( "vcat has included..." )

