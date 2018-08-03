

message( "Include vlog (ver.3)..." )

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

FILE( GLOB HEADERS_VLOGGER ${HEADERS_VLOGGER} "${VLIBS_PATH}/vlog/verror.h"   )
FILE( GLOB SOURCES_VLOGGER ${SOURCES_VLOGGER} "${VLIBS_PATH}/vlog/verror.cpp" )

#FILE( GLOB HEADERS_VLOGGER "${VLIBS_PATH}/vlog/*.h"   )
#FILE( GLOB SOURCES_VLOGGER "${VLIBS_PATH}/vlog/*.cpp" )


set ( V_HEADERS ${V_HEADERS} ${HEADERS_VLOGGER} )
set ( V_SOURCES ${V_SOURCES} ${SOURCES_VLOGGER} )

message( "vlog (ver.3) included" )

