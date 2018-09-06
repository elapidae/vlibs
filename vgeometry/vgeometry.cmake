message( "Include vgeometry..." )

include_directories( "${VLIBS_DIR}/vgeometry/" )

FILE(GLOB HEADERS_VGEOMETRY "${VLIBS_DIR}/vgeometry/*.h"   )
FILE(GLOB SOURCES_VGEOMETRY "${VLIBS_DIR}/vgeometry/*.cpp" )

set(V_HEADERS ${V_HEADERS} ${HEADERS_VGEOMETRY})
set(V_SOURCES ${V_SOURCES} ${SOURCES_VGEOMETRY})

message( "vgeometry included" )
