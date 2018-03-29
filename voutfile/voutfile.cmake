

message( "Include VOutFile..." )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories( "${VLIBS_PATH}/voutfile/" )

FILE( GLOB HEADERS_VOutFile "${VLIBS_PATH}/voutfile/voutfile.h"   )
FILE( GLOB SOURCES_VOutFile "${VLIBS_PATH}/voutfile/voutfile.cpp" )

FILE( GLOB HEADERS_VOutFile ${HEADERS_VOutFile} "${VLIBS_PATH}/voutfile/voutfile_withrotate.h"   )
FILE( GLOB SOURCES_VOutFile ${SOURCES_VOutFile} "${VLIBS_PATH}/voutfile/voutfile_withrotate.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VOutFile} )
set ( SOURCES ${SOURCES} ${SOURCES_VOutFile} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VOutFile} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VOutFile} )

message( "VOutFile included..." )

