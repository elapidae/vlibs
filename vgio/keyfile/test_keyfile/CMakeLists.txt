cmake_minimum_required(VERSION 2.8)

project(test_keyfile)

#add_executable(${PROJECT_NAME} "main.cpp")
#include_directories("${VLIBS_PATH}/vgeometry/tests" )

set( VLIBS_DIR "../../.." )

include( "${VLIBS_DIR}/vgio/keyfile/keyfile.cmake" )

FILE( GLOB T_SOURCES "*.cpp" )

add_executable(${PROJECT_NAME} ${T_SOURCES} ${V_SOURCES} )

find_library(GTEST_LIBRARY NAMES libgtest.a PATHS ${EXT_LIBS_PATH})
set(GTEST_LIBRARYS ${GTEST_LIBRARYS} ${GTEST_LIBRARY})

# libgtest_main
find_library(GTEST_MAIN_LIBRARY NAMES libgtest_main.a PATHS ${EXT_LIBS_PATH})
set(GTEST_MAIN_LIBRARYS ${GTEST_MAIN_LIBRARYS} ${GTEST_MAIN_LIBRARY})


target_link_libraries(${PROJECT_NAME}
                   ${GTEST_LIBRARYS}
                   ${GTEST_MAIN_LIBRARYS}
                   ${V_LIBRARIES}
                   -lgtest
                   -lpthread
                   )
