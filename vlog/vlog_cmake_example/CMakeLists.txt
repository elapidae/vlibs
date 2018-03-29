cmake_minimum_required(VERSION 2.8)

project(vlog_cmake_example)

set ( VLIBS_PATH "../../../vlibs/" )
include( "${VLIBS_PATH}/vlog/vfilelog.cmake" )


add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCES} "main.cpp" )
