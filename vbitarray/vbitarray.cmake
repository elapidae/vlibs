

message( "Include VBitArray..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vbitarray/" )

FILE( GLOB HEADERS_VBitArray "${VLIBS_PATH}/vbitarray/vbitarray.h"   )
FILE( GLOB SOURCES_VBitArray "${VLIBS_PATH}/vbitarray/vbitarray.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VBitArray} )
set ( SOURCES ${SOURCES} ${SOURCES_VBitArray} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VBitArray} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VBitArray} )

message( "VBitArray included..." )

