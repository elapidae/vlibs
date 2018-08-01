

message( "Include vsignal..." )

include_directories( "${VLIBS_PATH}/vsignal/" )

FILE( GLOB_RECURSE HEADERS_VSIGNAL "${VLIBS_PATH}/vsignal/*.h"   )

set ( HEADERS ${HEADERS} ${HEADERS_VSIGNAL} )

message( "vsignal has included..." )

