message( "Include vgeometry..." )

include_directories( "${VLIBS_PATH}/vgeometry/" )

FILE(GLOB HEADERS_VGEOMETRY "${VLIBS_PATH}/vgeometry/*.h"   )
FILE(GLOB SOURCES_VGEOMETRY "${VLIBS_PATH}/vgeometry/*.cpp" )

set(V_HEADERS${V_HEADERS} ${HEADERS_VGEOMETRY})
set(V_SOURCES${V_SOURCES} ${SOURCES_VGEOMETRY})

message( "vgeometry included" )
