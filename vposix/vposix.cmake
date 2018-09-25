#========================================================================================
# vposix.cmake
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

if ( NOT  VPOSIX_INCLUDED )
    set ( VPOSIX_INCLUDED TRUE )

    message( "Include vposix..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vposix/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_errno.h") 
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vposix/vposix_files.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_errno.cpp") 
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vposix/vposix_files.cpp") 

    message( "vposix included" )

endif()
# vposix.cmake
#========================================================================================
