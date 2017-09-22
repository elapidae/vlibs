

message( "Include vgpioleg..." )

include( "${VLIBS_PATH}/varg/varg.cmake" )
include( "${VLIBS_PATH}/vfile/vfile.cmake" )

include_directories( "${VLIBS_PATH}/vgpioleg/" )

FILE( GLOB HEADERS_vgpioleg "${VLIBS_PATH}/vgpioleg/*.h"   )
FILE( GLOB SOURCES_vgpioleg "${VLIBS_PATH}/vgpioleg/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_vgpioleg} )
set ( SOURCES ${SOURCES} ${SOURCES_vgpioleg} )

message( "vgpioleg has included..." )

