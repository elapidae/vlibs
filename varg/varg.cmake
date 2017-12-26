

message( "Include varg..." )

include_directories( "${VLIBS_PATH}/varg/" )

FILE( GLOB HEADERS_VARG "${VLIBS_PATH}/varg/*.h"   )
FILE( GLOB SOURCES_VARG "${VLIBS_PATH}/varg/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_VARG} )
set ( SOURCES ${SOURCES} ${SOURCES_VARG} )

set ( INC_ALL ${INC_ALL} ${HEADERS_VARG} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VARG} )

message( "Varg has included..." )

