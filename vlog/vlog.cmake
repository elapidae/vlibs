

message( "Include vlog (ver.2)..." )

include( "${VLIBS_PATH}/vcat/vcat.cmake" )
include( "${VLIBS_PATH}/vstring/vstring.cmake" )
include( "${VLIBS_PATH}/vchrono/vchrono.cmake" )

include_directories( "${VLIBS_PATH}/vlog/" )

FILE( GLOB HEADERS_VLOGGER "${VLIBS_PATH}/vlog/vlog.h"   )
FILE( GLOB SOURCES_VLOGGER "${VLIBS_PATH}/vlog/vlog.cpp" )

FILE( GLOB HEADERS_VLOGGER ${HEADERS_VLOGGER} "${VLIBS_PATH}/vlog/vlog_pretty.h"   )
FILE( GLOB SOURCES_VLOGGER ${SOURCES_VLOGGER} "${VLIBS_PATH}/vlog/vlog_pretty.cpp" )

FILE( GLOB HEADERS_VLOGGER ${HEADERS_VLOGGER} "${VLIBS_PATH}/vlog/vlogger.h"   )
FILE( GLOB SOURCES_VLOGGER ${SOURCES_VLOGGER} "${VLIBS_PATH}/vlog/vlogger.cpp" )

FILE( GLOB HEADERS_VLOGGER ${HEADERS_VLOGGER} "${VLIBS_PATH}/vlog/vlogentry.h"   )
FILE( GLOB SOURCES_VLOGGER ${SOURCES_VLOGGER} "${VLIBS_PATH}/vlog/vlogentry.cpp" )

#FILE( GLOB HEADERS_VLOGGER ${HEADERS_VLOGGER} "${VLIBS_PATH}/vlog/*.h"   )
#FILE( GLOB SOURCES_VLOGGER ${SOURCES_VLOGGER} "${VLIBS_PATH}/vlog/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VLOGGER} )
set ( SOURCES ${SOURCES} ${SOURCES_VLOGGER} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VLOGGER} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VLOGGER} )

message( "vlog (ver.2) included" )

