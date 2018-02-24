

message( "Include vgeometry..." )

include( "${VLIBS_PATH}/vbytearray/vbytearray.cmake" )
include( "${VLIBS_PATH}/vstring/vstring.cmake" )

include_directories( "${VLIBS_PATH}/vgeometry/" )

FILE( GLOB HEADERS_VGEOMETRY "${VLIBS_PATH}/vgeometry/*.h"   )
FILE( GLOB SOURCES_VGEOMETRY "${VLIBS_PATH}/vgeometry/*.cpp" )

FILE( GLOB HEADERS_VGEOMETRY_ALG "${VLIBS_PATH}/vgeometry/valgorithms/*.h"   )
FILE( GLOB SOURCES_VGEOMETRY_ALG "${VLIBS_PATH}/vgeometry/valgorithms/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VGEOMETRY} ${HEADERS_VGEOMETRY_ALG} )
set ( SOURCES ${SOURCES} ${SOURCES_VGEOMETRY} ${SOURCES_VGEOMETRY_ALG} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VGEOMETRY} ${HEADERS_VGEOMETRY_ALG} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VGEOMETRY} ${SOURCES_VGEOMETRY_ALG} )

message( "vgeometry included" )

