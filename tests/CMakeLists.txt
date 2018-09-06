cmake_minimum_required(VERSION 2.8)

project(tests)

set( VLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vlibs" )


# надо удалить --------------------------------------------------------------------------
# надо просто удалить, а модули должны использовать:
include( "${VLIBS_DIR}/c++11/c++11.cmake" )
# надо удалить --------------------------------------------------------------------------




add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory("${VLIBS_DIR}/vgio/keyfile/test_keyfile/")

# VLIBS_PATH устарела, далее от нее надо избавиться.
#set( VLIBS_PATH  "${VLIBS_DIR}" )
add_subdirectory("${VLIBS_DIR}/vgeometry/tests/")


add_subdirectory("${VLIBS_DIR}/vcrc/test_vcrc/")
add_subdirectory("${VLIBS_DIR}/vstring/test_vstring/")
