

message( "Include vchrono..." )

include_directories( "${VLIBS_PATH}/vchrono/" )

FILE( GLOB HEADERS_VCHRONO "${VLIBS_PATH}/vchrono/*.h"   )
FILE( GLOB SOURCES_VCHRONO "${VLIBS_PATH}/vchrono/*.cpp" )

set ( V_HEADERS ${V_HEADERS} ${HEADERS_VCHRONO} )
set ( V_SOURCES ${V_SOURCES} ${SOURCES_VCHRONO} )

message( "VCHRONO has included..." )

