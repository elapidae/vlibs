

message( "Include vimage..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vimage/" )

FILE( GLOB HEADERS_vimage "${VLIBS_PATH}/vimage/vimage_opencv.h"   )
FILE( GLOB SOURCES_vimage "${VLIBS_PATH}/vimage/vimage_opencv.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vimage} )
set ( SOURCES ${SOURCES} ${SOURCES_vimage} )

set ( INC_ALL ${INC_ALL} ${HEADERS_vimage} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_vimage} )

message( "vimage included..." )

