cmake_minimum_required(VERSION 2.8)

project(tests)

set( VLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vlibs" )

# VLIBS_PATH устарела, далее от нее надо избавиться.
set( VLIBS_PATH  "${VLIBS_DIR}" )



# надо удалить --------------------------------------------------------------------------
add_definitions( -std=c++11 )
set( CPP_11_STANDARD_INCLUDED TRUE )
# надо просто удалить, а модули должны использовать:
#include( "${VLIBS_DIR}/c++11/c++11.cmake" )
# надо удалить --------------------------------------------------------------------------




add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory("${VLIBS_PATH}/vgeometry/tests/")
add_subdirectory("${VLIBS_PATH}/vgio/keyfile/test_keyfile/")
