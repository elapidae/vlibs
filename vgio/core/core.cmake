#----------------------------------------------------------------------------------------
#   UPD от 01-08-2018 -- Описание устарело, концепции поменялись, требуйте долива пива.
#
#
#   VIO -- обёртка вокруг библиотек glib и gio (стандартные библиотеки linux систем).
#
#   Для подключения, следует:
#       1. указать путь к папке vlibs через переменную VLIBS_DIR:
#           set( VLIBS_DIR "../vlibs" )
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


#========================================================================================
if ( NOT  VGIO_CORE_INCLUDED )
    set ( VGIO_CORE_INCLUDED TRUE )
    message( "about VGIO core (Glib & Gio)..." )
    #------------------------------------------------------------------------------------

    find_package(PkgConfig)

    if( NOT PKG_CONFIG_FOUND )
        message( FATAL_ERROR "Нужен pkgconfig для подключения glib." )
    endif()

    pkg_search_module( GLib_PKG REQUIRED glib-2.0 )

    if ( NOT GLib_PKG_FOUND )
        message( FATAL_ERROR "glib not found" )
    else()
        message( "=== GLib_PKG was found === " )
    endif()

    set( V_LIBRARIES ${V_LIBRARIES} ${GLib_PKG_LIBRARIES} )

    include_directories( ${GLib_PKG_INCLUDE_DIRS} )

    set( VGIO_DIR "${VLIBS_DIR}/vgio" )

    #------------------------------------------------------------------------------------
    message( "VGIO core (Glib & Gio) included." )
endif() #VGIO_CORE_INCLUDED
#========================================================================================





#message( FATAL_ERROR ${GLib_PKG_INCLUDE_DIRS} )
#  message( ===================== ${GLib_PKG_LIBRARY_DIRS} )
#  message( ===================== ${GLib_PKG_LDFLAGS} )
#    <XPREFIX>_FOUND          ... set to 1 if module(s) exist
#    <XPREFIX>      ... only the libraries (w/o the '-l')
#    <XPREFIX>   ... the paths of the libraries (w/o the '-L')
#    <XPREFIX>_LDFLAGS        ... all required linker flags
#    <XPREFIX>_LDFLAGS_OTHER  ... all other linker flags
#    <XPREFIX>_INCLUDE_DIRS   ... the '-I' preprocessor flags (w/o the '-I')
#    <XPREFIX>_CFLAGS         ... all required cflags
#    <XPREFIX>_CFLAGS_OTHER   ... the other compiler flags

#include_directories( "${VLIBS_DIR}/vio/" )
# ---- glib-2.0 gio-2.0 connecting part ---------------------------------------------
# Каким-то образом люди подключают эти штуки, пока непонятно как, захардкоржено.
#set( GLib_LIBRARIES "-lglib-2.0 -lgobject-2.0 -lgio-2.0" )
#set( V_LIBRARIES ${V_LIBRARIES} ${GLib_LIBRARIES} )

#include_directories("/usr/include/glib-2.0/")
#include_directories("/usr/include/glib-2.0/glib/")
#include_directories("/usr/lib/x86_64-linux-gnu/glib-2.0/include")
#include_directories("/usr/lib/aarch64-linux-gnu/glib-2.0/include")
# ---- glib-2.0 gio-2.0 connecting part ---------------------------------------------

#    find_library( GLib_LIBRARY glib-2.0 HINTS ${GLib_PKG_LIBRARY_DIRS} )
#    set(GLib glib-2.0)

#message( FATAL_ERROR ${GLib_LIBRARY} )
#    if(GLib_LIBRARY AND NOT GLib_FOUND)
#      add_library(${GLib} SHARED IMPORTED)
#      set_property(TARGET ${GLib} PROPERTY IMPORTED_LOCATION "${GLib_LIBRARY}")
#      set_property(TARGET ${GLib} PROPERTY INTERFACE_COMPILE_OPTIONS "${GLib_PKG_CFLAGS_OTHER}")

#      find_path(GLib_INCLUDE_DIRS "glib.h"
#        HINTS ${GLib_PKG_INCLUDE_DIRS}
#        PATH_SUFFIXES "glib-2.0")

#      get_filename_component(GLib_LIBDIR "${GLib}" DIRECTORY)
#      find_path(GLib_CONFIG_INCLUDE_DIR "glibconfig.h"
#        HINTS
#          ${GLib_LIBDIR}
#          ${GLib_PKG_INCLUDE_DIRS}
#        PATHS
#          "${CMAKE_LIBRARY_PATH}"
#        PATH_SUFFIXES
#          "glib-2.0/include"
#          "glib-2.0")
#      unset(GLib_LIBDIR)

#      if(GLib_CONFIG_INCLUDE_DIR)
#        file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MAJOR_VERSION REGEX "^#define GLIB_MAJOR_VERSION +([0-9]+)")
#        string(REGEX REPLACE "^#define GLIB_MAJOR_VERSION ([0-9]+)$" "\\1" GLib_MAJOR_VERSION "${GLib_MAJOR_VERSION}")
#        file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MINOR_VERSION REGEX "^#define GLIB_MINOR_VERSION +([0-9]+)")
#        string(REGEX REPLACE "^#define GLIB_MINOR_VERSION ([0-9]+)$" "\\1" GLib_MINOR_VERSION "${GLib_MINOR_VERSION}")
#        file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MICRO_VERSION REGEX "^#define GLIB_MICRO_VERSION +([0-9]+)")
#        string(REGEX REPLACE "^#define GLIB_MICRO_VERSION ([0-9]+)$" "\\1" GLib_MICRO_VERSION "${GLib_MICRO_VERSION}")
#        set(GLib_VERSION "${GLib_MAJOR_VERSION}.${GLib_MINOR_VERSION}.${GLib_MICRO_VERSION}")
#        unset(GLib_MAJOR_VERSION)
#        unset(GLib_MINOR_VERSION)
#        unset(GLib_MICRO_VERSION)

#        list(APPEND GLib_INCLUDE_DIRS ${GLib_CONFIG_INCLUDE_DIR})
#        set_property(TARGET ${GLib} PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GLib_INCLUDE_DIRS}")
#      endif()
#    endif()

#    include(FindPackageHandleStandardArgs)
#    find_package_handle_standard_args(GLib
#        REQUIRED_VARS
#          GLib_LIBRARY
#          GLib_INCLUDE_DIRS
#        VERSION_VAR
#    GLib_VERSION)
#------------------------------------------------------------------------------------




# Может когда-нибудь найду более внятный способ подключения этой порнухи...
#set ( SHARED_LIBS ${SHARED_LIBS} GLib2 )
#message( " shared libs == ${SHARED_LIBS}" )

#CFLAGS = `pkg-config --cflags --libs gio-2.0`
#find_package(GTK2 REQUIRED)
#add_executable(${PROJECT} ${SOURCES} ${GTK2_LIBRARIES})


# ---- glib-2.0 gio-2.0 connecting part ---------------------------------------------
#set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
#set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )



#find_package(PkgConfig)

#if(PKG_CONFIG_FOUND)
#  pkg_search_module(GLib_PKG glib-2.0)
#endif()

#find_library(GLib_LIBRARY glib-2.0 HINTS ${GLib_PKG_LIBRARY_DIRS})
#set(GLib glib-2.0)

#if(GLib_LIBRARY AND NOT GLib_FOUND)
#  add_library(${GLib} SHARED IMPORTED)
#  set_property(TARGET ${GLib} PROPERTY IMPORTED_LOCATION "${GLib_LIBRARY}")
#  set_property(TARGET ${GLib} PROPERTY INTERFACE_COMPILE_OPTIONS "${GLib_PKG_CFLAGS_OTHER}")

#  find_path(GLib_INCLUDE_DIRS "glib.h"
#    HINTS ${GLib_PKG_INCLUDE_DIRS}
#    PATH_SUFFIXES "glib-2.0")

#  get_filename_component(GLib_LIBDIR "${GLib}" DIRECTORY)
#  find_path(GLib_CONFIG_INCLUDE_DIR "glibconfig.h"
#    HINTS
#      ${GLib_LIBDIR}
#      ${GLib_PKG_INCLUDE_DIRS}
#    PATHS
#      "${CMAKE_LIBRARY_PATH}"
#    PATH_SUFFIXES
#      "glib-2.0/include"
#      "glib-2.0")
#  unset(GLib_LIBDIR)

#  if(GLib_CONFIG_INCLUDE_DIR)
#    file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MAJOR_VERSION REGEX "^#define GLIB_MAJOR_VERSION +([0-9]+)")
#    string(REGEX REPLACE "^#define GLIB_MAJOR_VERSION ([0-9]+)$" "\\1" GLib_MAJOR_VERSION "${GLib_MAJOR_VERSION}")
#    file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MINOR_VERSION REGEX "^#define GLIB_MINOR_VERSION +([0-9]+)")
#    string(REGEX REPLACE "^#define GLIB_MINOR_VERSION ([0-9]+)$" "\\1" GLib_MINOR_VERSION "${GLib_MINOR_VERSION}")
#    file(STRINGS "${GLib_CONFIG_INCLUDE_DIR}/glibconfig.h" GLib_MICRO_VERSION REGEX "^#define GLIB_MICRO_VERSION +([0-9]+)")
#    string(REGEX REPLACE "^#define GLIB_MICRO_VERSION ([0-9]+)$" "\\1" GLib_MICRO_VERSION "${GLib_MICRO_VERSION}")
#    set(GLib_VERSION "${GLib_MAJOR_VERSION}.${GLib_MINOR_VERSION}.${GLib_MICRO_VERSION}")
#    unset(GLib_MAJOR_VERSION)
#    unset(GLib_MINOR_VERSION)
#    unset(GLib_MICRO_VERSION)

#    list(APPEND GLib_INCLUDE_DIRS ${GLib_CONFIG_INCLUDE_DIR})
#    set_property(TARGET ${GLib} PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GLib_INCLUDE_DIRS}")
#  endif()
#endif()

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(GLib
#    REQUIRED_VARS
#      GLib_LIBRARY
#      GLib_INCLUDE_DIRS
#    VERSION_VAR
#GLib_VERSION)
