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
    message( "== including vgit impl... ===" )

    # MAIN_DIR testing and defining. ----------------------------------------------------
    if ( NOT MAIN_DIR )
        set ( MAIN_DIR "${CMAKE_SOURCE_DIR}" )
        message( ">>>>>>>> Variable MAIN_DIR has not set, "
                 "so now MAIN_DIR=${MAIN_DIR} <<<<<<<<" )
    endif()

    # hash ------------------------------------------------------------------------------
    #   Проверку а ошибки делать имеет смысл только в первом вызове, далее по накатанной.
    execute_process( COMMAND git log -n 1 --pretty=format:"%H"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_HASH
                     ERROR_VARIABLE  VGIT_ERROR )

    if ( NOT VGIT_HASH )
        message( FATAL_ERROR ">>>>>>>> GIT ERROR: \"${VGIT_ERROR}\" "
                 "(скорее всего, в папке еще нету репа, сделайте "
                 "git init && git add . && git commit) <<<<<<<<" )
    endif()

    string(REGEX REPLACE "[\"\r\n]+" "" VGIT_HASH ${VGIT_HASH})
    add_definitions( -DVGIT_HASH_ELPD=${VGIT_HASH} )

    # revcount --------------------------------------------------------------------------
    #   Надо найти способ вырезать лишние переносы строки
    execute_process( COMMAND git rev-list HEAD --count
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_REVCOUNT )

    string(REGEX REPLACE "[\"\r\n]+" "" VGIT_REVCOUNT ${VGIT_REVCOUNT})
    add_definitions( -DVGIT_REVCOUNT_ELPD=${VGIT_REVCOUNT} )

    # branch ----------------------------------------------------------------------------
    execute_process( COMMAND git symbolic-ref --short HEAD
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_BRANCH )

    if ( NOT VGIT_BRANCH )      #   На случай оторванной головы.
        set( VGIT_BRANCH " " )  #   Когда отоврана, команда дает ошибку и переменная не
    endif()                     #   инициализируется. REGEX дает ошибку...
    string(REGEX REPLACE "[\"\r\n]+" "" VGIT_BRANCH ${VGIT_BRANCH})
    add_definitions( -DVGIT_BRANCH_ELPD=${VGIT_BRANCH} )

    # author ----------------------------------------------------------------------------
    execute_process( COMMAND git log -n 1 --pretty=format:"%an"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_AUTHOR )

    string(REGEX REPLACE "[\"\r\n]+" "" VGIT_AUTHOR ${VGIT_AUTHOR})
    add_definitions( -DVGIT_AUTHOR_ELPD=${VGIT_AUTHOR} )

    # date ------------------------------------------------------------------------------
    execute_process( COMMAND git log -n 1 --pretty=format:"%aI"
                     WORKING_DIRECTORY ${MAIN_DIR}
                     OUTPUT_VARIABLE VGIT_DATE )

    string(REGEX REPLACE "[\"\r\n]+" "" VGIT_DATE ${VGIT_DATE})
    add_definitions( -DVGIT_DATE_ELPD=${VGIT_DATE} )

    # -----------------------------------------------------------------------------------
    message( "Catched git hash: ${VGIT_HASH}"
                  ", rev-count: ${VGIT_REVCOUNT}"
                     ", branch: ${VGIT_BRANCH}"
                     ", author: ${VGIT_AUTHOR}"
                       ", date: ${VGIT_DATE}" )

    message( "=== vgit impl included ===" )

    # -----------------------------------------------------------------------------------
endif()
# vgit_impl.cmake
#========================================================================================
