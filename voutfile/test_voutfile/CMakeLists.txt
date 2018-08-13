cmake_minimum_required(VERSION 2.8)

project(test_voutfile)


#set ( VLIBS_DIR "../.." )
include( "${VLIBS_DIR}/voutfile/voutfile_with_rotate.cmake" )


add_executable( ${PROJECT_NAME} "main.cpp" ${V_SOURCES} )
