cmake_minimum_required(VERSION 2.8)


set( VLIBS_DIR "../.." )

include( "${VLIBS_DIR}/vwatchdog/vwatchdog.cmake" )

project(devel_vwatchdog)
add_executable(${PROJECT_NAME} ${V_HEADERS} ${V_SOURCES} "main.cpp")
