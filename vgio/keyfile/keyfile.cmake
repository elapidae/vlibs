#========================================================================================
# keyfile.cmake
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

if ( NOT  VGIO_KEYFILE_INCLUDED )
    set ( VGIO_KEYFILE_INCLUDED TRUE )

    message( "Include VGIO keyfile..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/vgio/error/error.cmake" )
    include( "${VLIBS_DIR}/vgio/core/impl/helpers.cmake" )

    include_directories( "${VLIBS_DIR}/vgio/keyfile" )

    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile.cpp")
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile_schema.cpp")

    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile.h")
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vgio/keyfile/vgio_keyfile_schema.h")

    add_definitions( -DVGIO_KEYFILE_INCLUDED_ELPD )
    #>>> Stop your code here ------------------------------------------------------------


    message( "VGIO keyfile included" )

endif()
# keyfile.cmake
#========================================================================================
