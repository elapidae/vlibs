#========================================================================================
# voutfile.cmake
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

if ( NOT  VOUTFILE_WITH_ROTATE_INCLUDED )
    set ( VOUTFILE_WITH_ROTATE_INCLUDED TRUE )

    message( "Include voutfile with rotate..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vcat/vcat.cmake" )
    include( "${VLIBS_DIR}/voutfile/voutfile.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/voutfile/")
    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/voutfile/voutfile_with_rotate.h")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/voutfile/voutfile_with_rotate.cpp")

    message( "voutfile with rotate included" )

endif()
# voutfile.cmake
#========================================================================================
