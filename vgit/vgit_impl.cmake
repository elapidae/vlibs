#########################################################################################
##
##  VLIBS codebase, NIIAS
##
##  Authors:
##  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
##  Nadezhda Churikova aka claorisel    claorisel@gmail.com
##  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
##  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
##
##  GNU Lesser General Public License Usage
##  This file may be used under the terms of the GNU Lesser General Public License
##  version 3 as published by the Free Software Foundation and appearing in the file
##  LICENSE.LGPL3 included in the packaging of this file. Please review the following
##  information to ensure the GNU Lesser General Public License version 3 requirements
##  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
#########################################################################################


#========================================================================================
#   NB! Краткие комментарии см. в vgit_impl.pri
#========================================================================================


#========================================================================================
if ( NOT  VGIT_IMPL_INCLUDED )
    set ( VGIT_IMPL_INCLUDED TRUE )
    message( "Include vgit impl..." )

    #====================================================================================
    # message for copy-pasting to a project. --------------------------------------------
    if ( NOT MAIN_DIR )
        message( "===================================================" )
        message( "Write it into general project:" )
        message( "set \( MAIN_DIR \"\${CMAKE_CURRENT_SOURCE_DIR}\" \)" )
        message( "===================================================" )
        message( FATAL_ERROR "<see above>" )
    endif()
    #====================================================================================
    # hash ------------------------------------------------------------------------------
    execute_process( COMMAND git log -n 1 --pretty=format:"%H"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_HASH
                     ERROR_VARIABLE  VGIT_ERROR )

    if ( ERROR_VARIABLE )
        message( FATAL_ERROR "Git error: ${VGIT_ERROR}" )
    else()
        message( "Current git hash: ${VGIT_HASH}" )
    endif()

    add_definitions( -DVGIT_HASH_ELPD=${VGIT_HASH} )
    # revcount --------------------------------------------------------------------------
    #   Надо найти способ вырезать лишние переносы строки
    #execute_process( COMMAND git rev-list HEAD --count
    #                 WORKING_DIRECTORY ${MAIN_DIR}
    #                 OUTPUT_VARIABLE VGIT_REVCOUNT )
    #message( "Current git rev-count: ${VGIT_REVCOUNT}" )
    #add_definitions( -DVGIT_REVCOUNT_ELPD=${VGIT_REVCOUNT} ) пока не можем извлечь :((
    # date ------------------------------------------------------------------------------
    execute_process( COMMAND git log -n 1 --pretty=format:"%aI"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_DATE )

    message( "Current git date: ${VGIT_DATE}" )
    add_definitions( -DVGIT_DATE_ELPD=${VGIT_DATE} )
    # author ----------------------------------------------------------------------------
    execute_process( COMMAND git log -n 1 --pretty=format:"%an"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_AUTHOR )

    message( "Current git author: ${VGIT_AUTHOR}" )
    add_definitions( -DVGIT_AUTHOR_ELPD=${VGIT_AUTHOR} )
    # branch ----------------------------------------------------------------------------
    #   Надо найти способ сделать парсинг и убить возможные последствия отрезанной головы
    #execute_process( COMMAND ${VLIBS_DIR}/vgit/extract_branch.sh .
    #                 WORKING_DIRECTORY ${MAIN_DIR}
    #                 OUTPUT_VARIABLE VGIT_BRANCH )
    #message( "Current git author: ${VGIT_BRANCH}" )
    #add_definitions( -DVGIT_BRANCH_ELPD=${VGIT_BRANCH} ) пока не можем извлечь :((
    #====================================================================================

    include_directories( "${VLIBS_DIR}/vgit/")
    
    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgit/vgit.h"   )
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgit/vgit.cpp" )

    message( "vgit impl included" )
    #====================================================================================
endif()
# vgit_impl.cmake
#========================================================================================
