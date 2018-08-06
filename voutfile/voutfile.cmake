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

if ( NOT  VOUTFILE_INCLUDED )
    set ( VOUTFILE_INCLUDED TRUE )

    message( "Include voutfile..." )

    #<<< Start your code here -----------------------------------------------------------    
    #   NB! Файл был отредактирован, перезапись может добавить ненужные поля.

    include( "${VLIBS_DIR}/c++11/c++11.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/voutfile/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/voutfile/voutfile.h") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/voutfile/voutfile.cpp") 

    message( "voutfile included" )

endif()
# voutfile.cmake
#========================================================================================
