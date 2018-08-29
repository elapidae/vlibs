#========================================================================================
# vapp_args_parser.cmake
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

if ( NOT  VAPP_ARGS_PARSER_INCLUDED )
    set ( VAPP_ARGS_PARSER_INCLUDED TRUE )

    message( "Include vapp_args_parser..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vapp_args_parser/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vapp_args_parser/vapp_args_parser.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vapp_args_parser/vapp_args_parser.cpp") 

    message( "vapp_args_parser included" )

endif()
# vapp_args_parser.cmake
#========================================================================================
