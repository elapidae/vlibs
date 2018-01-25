

message( "Include VByteArray..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vbytearray/" )

FILE( GLOB HEADERS_VByteArray "${VLIBS_PATH}/vbytearray/*.h"   )
FILE( GLOB SOURCES_VByteArray "${VLIBS_PATH}/vbytearray/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VByteArray} )
set ( SOURCES ${SOURCES} ${SOURCES_VByteArray} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VByteArray} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VByteArray} )

message( "VByteArray included..." )

