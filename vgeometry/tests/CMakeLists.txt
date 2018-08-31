project(tests_vgeometry C CXX)

include_directories("${VLIBS_DIR}/vgeometry/tests" )

include( "${VLIBS_DIR}/vgeometry/vgeometry.cmake" )

#FILE(GLOB T_SOURCES "${VLIBS_DIR}/vgeometry/*.cpp" "*.cpp")
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
                   -lgtest
                   -lpthread
                   )

