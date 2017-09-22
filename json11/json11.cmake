

message( "Include json11..." )

include_directories( "${VLIBS_PATH}/json11/" )

FILE( GLOB HEADERS_json11 "${VLIBS_PATH}/json11/*.h"   )
FILE( GLOB SOURCES_json11 "${VLIBS_PATH}/json11/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_json11} )
set ( SOURCES ${SOURCES} ${SOURCES_json11} )

message( "json11 included" )

