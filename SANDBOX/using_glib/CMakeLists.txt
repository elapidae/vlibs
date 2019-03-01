cmake_minimum_required(VERSION 2.8)

project(using_glib)
add_executable(${PROJECT_NAME} "main.cpp")

set( VLIBS_DIR "../../vlibs" )
include( "${VLIBS_DIR}/vgio/keyfile/keyfile.cmake" )

message( "GDIR: '${GLib_PKG_INCLUDE_DIRS}'" )
message( "GLIB: '${GLib_PKG_LIBRARIES}'" )

