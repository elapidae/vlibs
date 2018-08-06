#========================================================================================
# {{vlib_name}}.cmake
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
{% set vlib_name_upper = vlib_name|upper() %}
if ( NOT  {{vlib_name_upper}}_INCLUDED )
    set ( {{vlib_name_upper}}_INCLUDED TRUE )

    message( "Include {{vlib_name}}..." )

    #<<< Start your code here -----------------------------------------------------------
{{manual_code}}    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/{{vlib_name}}/")

    {% for item in headers %}
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/{{vlib_name}}/{{item}}") {% endfor %}
    {% for item in sources %}
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/{{vlib_name}}/{{item}}") {% endfor %}

    message( "{{vlib_name}} included" )

endif()
# {{vlib_name}}.cmake
#========================================================================================

