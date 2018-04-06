

message( "Include vcat..." )

include_directories( "${VLIBS_PATH}/vcat/" )

FILE( GLOB HEADERS_Vcat "${VLIBS_PATH}/vcat/*.h"   )
FILE( GLOB SOURCES_Vcat "${VLIBS_PATH}/vcat/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_Vcat} )
set ( SOURCES ${SOURCES} ${SOURCES_Vcat} )

set ( INC_ALL ${INC_ALL} ${HEADERS_Vcat} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_Vcat} )

if( NOT CPP11_STANDARD_INCLUDED )
    add_definitions( -std=c++11 )
    set ( CPP11_STANDARD_INCLUDED TRUE )
endif()

message( "vcat has included..." )

