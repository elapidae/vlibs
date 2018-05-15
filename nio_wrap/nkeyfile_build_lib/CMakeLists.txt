cmake_minimum_required( VERSION 2.8 )
cmake_policy(SET CMP0048 NEW)

project( nkeyfile CXX )

set( CMAKE_VERBOSE_MAKEFILE ON )

set( CMAKE_CXX_FLAGS " -std=c++11 -O2 ${CMAKE_CXX_FLAGS}" )

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib )

include_directories(.)

set( INCLUDE ../nerror.h
             ../nkeyfile.h
             ../impl/nconvertinghelper.h )

set( SOURCE ../nerror.cpp
            ../nkeyfile.cpp
            ../impl/nconvertinghelper.cpp )

find_package( GTK2 REQUIRED )
include_directories( ${GTK2_INCLUDE_DIRS} )

add_library( ${PROJECT_NAME} STATIC ${INCLUDE} ${SOURCE} ${GTK2_LIBRARIES} )

install( TARGETS ${PROJECT_NAME}
         ARCHIVE DESTINATION /usr/local/lib
         LIBRARY DESTINATION /usr/local/lib )

install( FILES ../nerror.h
               ../nkeyfile.h DESTINATION /usr/local/include/nkeyfile )

