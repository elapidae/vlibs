

message( "Include vthread..." )

include( "${VLIBS_PATH}/vsignal/vsignal.cmake" )
#include( "${VLIBS_PATH}/vlogger/vlogger.cmake" )

#add_definitions( -DVTHREAD_USE_PTHREAD )

include_directories( "${VLIBS_PATH}/vthread/" )

FILE( GLOB HEADERS_VTHREAD "${VLIBS_PATH}/vthread/*.h"   )
FILE( GLOB SOURCES_VTHREAD "${VLIBS_PATH}/vthread/*.cpp" )

FILE( GLOB HEADERS_VTHREAD ${HEADERS_VTHREAD} "${VLIBS_PATH}/vthread/vsemaphore/*.h"   )
FILE( GLOB SOURCES_VTHREAD ${SOURCES_VTHREAD} "${VLIBS_PATH}/vthread/vsemaphore/*.cpp" )

FILE( GLOB HEADERS_VTHREAD ${HEADERS_VTHREAD} "${VLIBS_PATH}/vthread/vthreadqueue/*.h"  )
FILE( GLOB SOURCES_VTHREAD ${SOURCES_VTHREAD} "${VLIBS_PATH}/vthread/vthreadqueue/*.cpp")

FILE( GLOB HEADERS_VTHREAD ${HEADERS_VTHREAD} "${VLIBS_PATH}/vthread/impl/*.h"   )
FILE( GLOB SOURCES_VTHREAD ${SOURCES_VTHREAD} "${VLIBS_PATH}/vthread/impl/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VTHREAD} )
set ( SOURCES ${SOURCES} ${SOURCES_VTHREAD} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VTHREAD} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VTHREAD} )

message( "vthread has included..." )

