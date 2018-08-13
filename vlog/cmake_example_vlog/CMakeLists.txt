cmake_minimum_required(VERSION 2.8)

project(vlog_cmake_example)

set ( VLIBS_DIR "../../../vlibs/" )
include( "${VLIBS_DIR}/vlog/vfilelog.cmake" )

include( "${VLIBS_DIR}/vgio/keyfile/keyfile.cmake" )

add_executable( ${PROJECT_NAME} ${V_HEADERS} ${V_SOURCES} "main.cpp" )

target_link_libraries ( ${PROJECT_NAME} ${V_LIBRARIES} )
