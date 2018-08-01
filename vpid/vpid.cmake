

message( "Include VPid..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include( "${VLIBS_PATH}/vlog/vlog.cmake" )
include( "${VLIBS_PATH}/voutfile/voutfile.cmake" )

include_directories( "${VLIBS_PATH}/vpid/" )

FILE( GLOB HEADERS_vpid "${VLIBS_PATH}/vpid/vpid_saver.h"   )
FILE( GLOB SOURCES_vpid "${VLIBS_PATH}/vpid/vpid_saver.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vpid} )
set ( SOURCES ${SOURCES} ${SOURCES_vpid} )

set ( INC_ALL ${INC_ALL} ${HEADERS_vpid} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_vpid} )

message( "VPid included..." )
