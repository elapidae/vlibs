#----------------------------------------------------------------------------------------
#   NIO -- обёртка вокруг библиотек glib и gio (стандартные библиотеки linux систем).
#
#   Для подключения, следует:
#       1. указать путь к текущей обертке через переменную NIO_PATH:
#           set( NIO_PATH "../vlibs/nio_wrap" )
#
#       2. включить файл nio_wrap.cmake в проект:
#           include( "${NIO_PATH}/nio_wrap.cmake" )
#       При правильном включении будет создана переменная ${NIO_TARGET_LIBS}.
#       Будут заполнены файлами переменные HEADERS, INC_ALL, SOURCES и SRC_ALL.
#
#       3. Эту переменную необходимо включить в команду target_link_libraries.
#           Это может быть сделано внесением этой перемннной непосредственно в команду
#           цели, либо её внесением в переменные среды, например,
#               # через к-л переменные.
#               set(SHARED_LIBS ${SHARED_LIBS} ${NIO_TARGET_LIBS}) )
#               # или напрямую.
#               target_link_libraries ( ${PROJECT_NAME} ${NIO_TARGET_LIBS} )
#----------------------------------------------------------------------------------------


message( "NIO wrapper (Glib & Gio)..." )

# ---- NIO wrapping part ----------------------------------------------------------------
include_directories( "${NIO_PATH}/" )

FILE( GLOB HEADERS_NIO "${NIO_PATH}/*.h"   )
FILE( GLOB SOURCES_NIO "${NIO_PATH}/*.cpp" )

FILE( GLOB HEADERS_NIO_IMPL "${NIO_PATH}/impl/*.h"   )
FILE( GLOB SOURCES_NIO_IMPL "${NIO_PATH}/impl/*.cpp" )


include_directories( "${NIO_PATH}/network" )

FILE( GLOB HEADERS_NIO_NETWORK "${NIO_PATH}/network/*.h"   )
FILE( GLOB SOURCES_NIO_NETWORK "${NIO_PATH}/network/*.cpp" )


set ( HEADERS ${HEADERS} ${HEADERS_NIO} ${HEADERS_NIO_IMPL} ${HEADERS_NIO_NETWORK} )
set ( INC_ALL ${INC_ALL} ${HEADERS_NIO} ${HEADERS_NIO_IMPL} ${HEADERS_NIO_NETWORK} )

set ( SOURCES ${SOURCES} ${SOURCES_NIO} ${SOURCES_NIO_IMPL} ${SOURCES_NIO_NETWORK} )
set ( SRC_ALL ${SRC_ALL} ${SOURCES_NIO} ${SOURCES_NIO_IMPL} ${SOURCES_NIO_NETWORK} )
# ---- NIO wrapping part ----------------------------------------------------------------


# ---- glib-2.0 gio-2.0 connecting part -------------------------------------------------
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )


include_directories("/usr/include/glib-2.0/")
include_directories("/usr/include/glib-2.0/glib/")
include_directories("/usr/lib/x86_64-linux-gnu/glib-2.0/include")
include_directories("/usr/lib/aarch64-linux-gnu/glib-2.0/include")
# ---- glib-2.0 gio-2.0 connecting part -------------------------------------------------


# ---- target link preparing  -----------------------------------------------------------
set ( NIO_TARGET_LIBS "-lglib-2.0 -lgobject-2.0 -lgio-2.0" )
set ( TARGET_LIBS ${TARGET_LIBS} ${NIO_TARGET_LIBS} )
# ---- target link preparing  -----------------------------------------------------------


message( "NIO wrapper (Glib & Gio) included..." )









# Может когда-нибудь найду более внятный способ подключения этой порнухи...
#set ( SHARED_LIBS ${SHARED_LIBS} GLib2 )
#message( " shared libs == ${SHARED_LIBS}" )

#CFLAGS = `pkg-config --cflags --libs gio-2.0`
#find_package(GTK2 REQUIRED)
#add_executable(${PROJECT} ${SOURCES} ${GTK2_LIBRARIES})
