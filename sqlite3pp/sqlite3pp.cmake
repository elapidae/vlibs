

message( "Include sqlite3pp..." )


include_directories( "${VLIBS_PATH}/sqlite3pp/" )

FILE( GLOB HEADERS_SQLITE3PP "${VLIBS_PATH}/sqlite3pp/*.h"   )
FILE( GLOB SOURCES_SQLITE3PP "${VLIBS_PATH}/sqlite3pp/*.cpp" )

set ( HEADERS ${HEADERS} ${HEADERS_SQLITE3PP} )
set ( SOURCES ${SOURCES} ${SOURCES_SQLITE3PP} )

set ( INC_ALL ${INC_ALL} ${HEADERS_SQLITE3PP} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_SQLITE3PP} )


set ( SQLITE3_TARGET_LIBS "-lsqlite3" )
set ( TARGET_LIBS ${TARGET_LIBS} ${SQLITE3_TARGET_LIBS} )


message( "sqlite3pp has included..." )

