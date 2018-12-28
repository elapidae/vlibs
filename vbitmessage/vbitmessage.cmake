

message( "Include vbitmessage..." )

include_directories( "${VLIBS_PATH}/vbitmessage/" )

FILE( GLOB HEADERS_Vbitmessage "${VLIBS_PATH}/vbitmessage/*.h"   )
FILE( GLOB SOURCES_Vbitmessage "${VLIBS_PATH}/vbitmessage/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_Vbitmessage} )
set ( SOURCES ${SOURCES} ${SOURCES_Vbitmessage} )

set ( INC_ALL ${INC_ALL} ${HEADERS_Vbitmessage} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_Vbitmessage} )

message( "vbitmessage has included..." )

