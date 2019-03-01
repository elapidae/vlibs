cmake_minimum_required(VERSION 2.8)

set( VLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../vlibs" )

project(test_ii)


#find_package(gtest REQUIRED)
find_library( GTEST_LIBRARY NAMES libgtest.a PATHS ${EXT_LIBS_PATH} )
#find_library( GTEST_LIBRARY NAMES libgtest.a  )
#set( GTEST_LIBRARYS ${GTEST_LIBRARYS} ${GTEST_LIBRARY} )
#find_package(GTest REQUIRED NAMES libgtest.a)
#include_directories(${GTEST_INCLUDE_DIR})
#add_subdirectory(lib/gtest-1.6.0)

enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


include( "${VLIBS_DIR}/vlog/vlog.cmake" )
#include( "${VLIBS_DIR}/vthread/vthread.cmake" )

set( TEST_II_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." )
include( "${TEST_II_DIR}/ii_serialization.cmake" )


add_executable( ${PROJECT_NAME} ${V_SOURCES} ${V_HEADERS} "main.cpp" )

# libgtest_main
find_library(GTEST_MAIN_LIBRARY NAMES libgtest_main.a PATHS ${EXT_LIBS_PATH})
set(GTEST_MAIN_LIBRARYS ${GTEST_MAIN_LIBRARYS} ${GTEST_MAIN_LIBRARY})
#message( ">>>>> ${GTEST_MAIN_LIBRARYS}" )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


target_link_libraries(${PROJECT_NAME}
                   ${GTEST_LIBRARYS}
                   ${GTEST_MAIN_LIBRARYS}
                   ${V_LIBRARIES}
                   -lgtest
                   -lpthread
                   )
