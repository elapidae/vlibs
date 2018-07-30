

message( "Include VString..." )

#set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vstring/" )

FILE( GLOB HEADERS_VString "${VLIBS_PATH}/vstring/*.h"   )
FILE( GLOB SOURCES_VString "${VLIBS_PATH}/vstring/*.cpp" )

set ( INC_ALL ${INC_ALL} ${HEADERS_VString} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VString} )

message( "VString included..." )

