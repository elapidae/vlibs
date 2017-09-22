

message( "Include vlogger..." )

include( "${VLIBS_PATH}/varg/varg.cmake" )
include( "${VLIBS_PATH}/json11/json11.cmake" )
include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )
include( "${VLIBS_PATH}/vdatetime/vdatetime.cmake" )

include_directories( "${VLIBS_PATH}/vlogger/" )

FILE( GLOB HEADERS_VLOGGER "${VLIBS_PATH}/vlogger/*.h"   )
FILE( GLOB SOURCES_VLOGGER "${VLIBS_PATH}/vlogger/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VLOGGER} )
set ( SOURCES ${SOURCES} ${SOURCES_VLOGGER} )

message( "vlogger included" )

