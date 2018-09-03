#========================================================================================
# vlog.cmake
#
#   NB! Ручная правка.
#
# Вносить изменения можно между строк:
#   #<<< Start your code here
#   Сохраненный код.
#   #>>> Stop your code here
# Все остальные изменения будут перезаписаны.
#
#========================================================================================


#========================================================================================

if ( NOT  VFILELOG_INCLUDED )
    set ( VFILELOG_INCLUDED TRUE )

    message( "Include vfilelog..." )

    #<<< Start your code here -----------------------------------------------------------
    #   NB! Файл вычищен от лишнего руками.
    include( "${VLIBS_DIR}/vlog/vlog.cmake" )
    include( "${VLIBS_DIR}/vdir/vdir.cmake" )
    #include( "${VLIBS_DIR}/voutfile/voutfile_with_rotate.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vlog/")

    

    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog_threaded.h")
    #set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog_keyfile.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vlog/vfilelog.h") 
    
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog_threaded.cpp")
    #set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog_keyfile.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vlog/vfilelog.cpp") 

    message( "vfilelog included" )

endif()
# vlog.cmake
#========================================================================================
