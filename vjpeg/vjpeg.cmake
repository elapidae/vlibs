#========================================================================================
# vjpeg.cmake
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

if ( NOT  VJPEG_INCLUDED )
    set ( VJPEG_INCLUDED TRUE )

    message( "Include vjpeg..." )

    #<<< Start your code here -----------------------------------------------------------
    message( "!!! NB! vjpeg NOT READY FOR DEPLOY! Need to include -ljpeg !!!" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vjpeg/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vjpeg/vjpeg.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vjpeg/vjpeg.cpp") 

    message( "vjpeg included" )

endif()
# vjpeg.cmake
#========================================================================================
