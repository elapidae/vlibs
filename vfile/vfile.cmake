#========================================================================================
# vfile.cmake
#
#
# Этот файл сгенерирован автоматически.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================

if ( NOT  VFILE_INCLUDED )
    set ( VFILE_INCLUDED TRUE )

    message( "Include vfile..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vposix/vposix.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vfile/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vfile/vfile.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vfile/vfile.cpp") 

    message( "vfile included" )

endif()
# vfile.cmake
#========================================================================================
