

message( "Include vserialsocket..." )

include( "${VLIBS_PATH}/vsignal/vsignal.cmake" )
include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )
include( "${VLIBS_PATH}/vthread/vthread.cmake" )

include_directories( "${VLIBS_PATH}/vserialsocket/" )

FILE( GLOB HEADERS_vserialsocket "${VLIBS_PATH}/vserialsocket/*.h"   )
FILE( GLOB SOURCES_vserialsocket "${VLIBS_PATH}/vserialsocket/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vserialsocket} )
set ( SOURCES ${SOURCES} ${SOURCES_vserialsocket} )

FILE( GLOB VSERIAL_README "${VLIBS_PATH}/vserialsocket/vserial-readme.txt" )


message( "vserialsocket has included..." )

