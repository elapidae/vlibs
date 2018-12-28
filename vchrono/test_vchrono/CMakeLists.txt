cmake_minimum_required(VERSION 2.8)

set( VLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." )


project(test_vchrono)


find_library( GTEST_LIBRARY NAMES libgtest.a PATHS ${EXT_LIBS_PATH} )
set( GTEST_LIBRARYS ${GTEST_LIBRARYS} ${GTEST_LIBRARY} )


include( "${VLIBS_DIR}/vchrono/vchrono.cmake" )
include( "${VLIBS_DIR}/vlog/vlog.cmake" )
include( "${VLIBS_DIR}/vstring/vstring.cmake" )

add_executable( ${PROJECT_NAME} ${V_HEADERS} ${V_SOURCES} "main.cpp" )

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
