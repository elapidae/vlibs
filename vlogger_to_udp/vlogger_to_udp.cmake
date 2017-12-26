

message( "Include vlogger to UDP..." )

include( "${VLIBS_PATH}/vlogger/vlogger.cmake" )

include_directories( "${VLIBS_PATH}/vlogger_to_udp/" )

FILE( GLOB HEADERS_VLOGGER2UDP "${VLIBS_PATH}/vlogger_to_udp/*.h"   )
FILE( GLOB SOURCES_VLOGGER2UDP "${VLIBS_PATH}/vlogger_to_udp/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VLOGGER2UDP} )
set ( SOURCES ${SOURCES} ${SOURCES_VLOGGER2UDP} )

message( "vlogger to UDP included" )

