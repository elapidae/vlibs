

message( "Include vdir..." )

include_directories( "${VLIBS_PATH}/vdir/" )

FILE( GLOB HEADERS_VDIR "${VLIBS_PATH}/vdir/vdir.h"   )
FILE( GLOB SOURCES_VDIR "${VLIBS_PATH}/vdir/vdir.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VDIR} )
set ( SOURCES ${SOURCES} ${SOURCES_VDIR} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VDIR} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VDIR} )

message( "vdir included" )

