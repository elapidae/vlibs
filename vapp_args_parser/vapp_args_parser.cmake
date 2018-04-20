

message( "Include VArgs parser..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/vapp_args_parser/" )

FILE( GLOB HEADERS_VArgsParser "${VLIBS_PATH}/vapp_args_parser/vapp_args_parser.h"   )
FILE( GLOB SOURCES_VArgsParser "${VLIBS_PATH}/vapp_args_parser/vapp_args_parser.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VArgsParser} )
set ( SOURCES ${SOURCES} ${SOURCES_VArgsParser} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VArgsParser} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VArgsParser} )

message( "VArgs parser included..." )

