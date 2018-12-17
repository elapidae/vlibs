#========================================================================================
# hdlc_parser.cmake
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

if ( NOT  HDLC_PARSER_INCLUDED )
    set ( HDLC_PARSER_INCLUDED TRUE )

    message( "Include hdlc_parser..." )

    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/hdlc_parser/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/hdlc_parser/hdlc_parser.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/hdlc_parser/hdlc_parser.cpp") 

    message( "hdlc_parser included" )

endif()
# hdlc_parser.cmake
#========================================================================================
