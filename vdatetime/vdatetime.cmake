

message( "Include vdatetime..." )

include_directories( "${VLIBS_PATH}/vdatetime/" )

FILE( GLOB_RECURSE HEADERS_vdatetime "${VLIBS_PATH}/vdatetime/*.h"   )
FILE( GLOB_RECURSE SOURCES_vdatetime "${VLIBS_PATH}/vdatetime/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vdatetime} )
set ( SOURCES ${SOURCES} ${SOURCES_vdatetime} )

set ( INC_ALL ${INC_ALL} ${HEADERS_vdatetime} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_vdatetime} )

message( "vdatetime has included..." )

