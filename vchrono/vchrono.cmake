

message( "Include vchrono..." )

include_directories( "${VLIBS_PATH}/vchrono/" )

FILE( GLOB HEADERS_VCHRONO "${VLIBS_PATH}/vchrono/*.h"   )
FILE( GLOB SOURCES_VCHRONO "${VLIBS_PATH}/vchrono/*.cpp" )

set ( INC_ALL ${INC_ALL} ${HEADERS_VCHRONO}  )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_VCHRONO} )

message( "VCHRONO has included..." )

