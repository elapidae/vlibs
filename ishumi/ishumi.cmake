

message( "Include ishumi..." )


include( "${VLIBS_PATH}/varg/varg.cmake" )
include( "${VLIBS_PATH}/json11/json11.cmake" )
include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )
include( "${VLIBS_PATH}/vdatetime/vdatetime.cmake" )

include_directories( "${VLIBS_PATH}/ishumi/" )

FILE( GLOB HEADERS_ISHUMI "${VLIBS_PATH}/ishumi/*.h"   )
FILE( GLOB SOURCES_ISHUMI "${VLIBS_PATH}/ishumi/*.cpp" )

FILE( GLOB HEADERS_ISHUMI "${VLIBS_PATH}/ishumi/ii_network/*.h"   )
FILE( GLOB SOURCES_ISHUMI "${VLIBS_PATH}/ishumi/ii_network/*.cpp" )


set ( HEADERS ${HEADERS} ${HEADERS_ISHUMI} )
set ( SOURCES ${SOURCES} ${SOURCES_ISHUMI} )

set ( INC_ALL ${INC_ALL} ${HEADERS_ISHUMI} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_ISHUMI} )


message( "ishumi included" )

