

message( "Include vtimer..." )

include_directories( "${VLIBS_PATH}/vtimer/" )

FILE( GLOB_RECURSE HEADERS_VTIMER "${VLIBS_PATH}/vtimer/*.h"   )
FILE( GLOB_RECURSE SOURCES_VTIMER "${VLIBS_PATH}/vtimer/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VTIMER} )
set ( SOURCES ${SOURCES} ${SOURCES_VTIMER} )

message( "vtimer has included..." )

