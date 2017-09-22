

message( "Include vparser_interface..." )

include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )

include_directories( "${VLIBS_PATH}/vparser_interface/" )

FILE(GLOB_RECURSE HEADERS_vparser_interface "${VLIBS_PATH}/vparser_interface/*.h"   )
FILE(GLOB_RECURSE SOURCES_vparser_interface "${VLIBS_PATH}/vparser_interface/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vparser_interface} )
set ( SOURCES ${SOURCES} ${SOURCES_vparser_interface} )

message( "vparser_interface has included..." )

