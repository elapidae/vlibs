

message( "Include vudpsocket..." )

include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )
include( "${VLIBS_PATH}/vlogger/vlogger.cmake" )
include( "${VLIBS_PATH}/vthread/vthread.cmake" )

include_directories( "${VLIBS_PATH}/vudpsocket/" )

FILE( GLOB_RECURSE HEADERS_VUDPSOCKET "${VLIBS_PATH}/vudpsocket/*.h"   )
FILE( GLOB_RECURSE SOURCES_VUDPSOCKET "${VLIBS_PATH}/vudpsocket/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VUDPSOCKET} )
set ( SOURCES ${SOURCES} ${SOURCES_VUDPSOCKET} )

message( "vudpsocket has included..." )

