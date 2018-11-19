cmake_minimum_required(VERSION 2.8)

project(tests)

set( VLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vlibs" )

add_executable( ${PROJECT_NAME} "main.cpp" )


add_subdirectory( "${VLIBS_DIR}/vcrc/test_vcrc/" )
add_subdirectory( "${VLIBS_DIR}/vstring/test_vstring/" )
add_subdirectory( "${VLIBS_DIR}/vgeometry/test_vgeometry/" )
add_subdirectory( "${VLIBS_DIR}/vgio/keyfile/test_keyfile/" )
add_subdirectory( "${VLIBS_DIR}/vapplication/test_vapplication/" )
