

message( "Include vsignal..." )

include_directories( "${VLIBS_PATH}/vsignal/" )

FILE( GLOB_RECURSE HEADERS_VSIGNAL "${VLIBS_PATH}/vsignal/*.h"   )
FILE( GLOB_RECURSE SOURCES_VSIGNAL "${VLIBS_PATH}/vsignal/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VSIGNAL} )
set ( SOURCES ${SOURCES} ${SOURCES_VSIGNAL} )

message( "vsignal has included..." )

