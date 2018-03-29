

message( "Include vfilelog..." )

include( "${VLIBS_PATH}/vlog/vlog.cmake" )
include( "${VLIBS_PATH}/voutfile/voutfile.cmake" )
include( "${VLIBS_PATH}/vthread/vthread.cmake" )

include_directories( "${VLIBS_PATH}/vlog/" )

FILE( GLOB HEADERS_VFILELOGGER "${VLIBS_PATH}/vlog/vfilelog.h"   )
FILE( GLOB SOURCES_VFILELOGGER "${VLIBS_PATH}/vlog/vfilelog.cpp" )

FILE( GLOB HEADERS_VFILELOGGER ${HEADERS_VFILELOGGER} "${VLIBS_PATH}/vlog/vfilelog_threaded.h"   )
FILE( GLOB SOURCES_VFILELOGGER ${SOURCES_VFILELOGGER} "${VLIBS_PATH}/vlog/vfilelog_threaded.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VFILELOGGER} )
set ( SOURCES ${SOURCES} ${SOURCES_VFILELOGGER} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VFILELOGGER} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VFILELOGGER} )

message( "vfilelog included" )

