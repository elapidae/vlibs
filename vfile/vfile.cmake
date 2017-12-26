

message( "Include vfile..." )

include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )

include_directories( "${VLIBS_PATH}/vfile/" )

FILE( GLOB HEADERS_vfile "${VLIBS_PATH}/vfile/*.h"   )
FILE( GLOB SOURCES_vfile "${VLIBS_PATH}/vfile/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vfile} )
set ( SOURCES ${SOURCES} ${SOURCES_vfile} )

message( "vfile has included..." )

