#========================================================================================
# {{vlib_name}}.pri
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
isEmpty(qi_{{vlib_name}}) {
    qi_{{vlib_name}} = 1;
    isEmpty(qi_not_print_pri_messages): message("=== {{vlib_name}} appended ===")

    isEmpty(VLIBS_DIR): error("{{vlib_name}}: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
{{manual_code}}    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/{{vlib_name}}

    {% for item in headers %}
    HEADERS     += $$VLIBS_DIR/{{vlib_name}}/{{item}} {% endfor %}
    {% for item in sources %}
    SOURCES     += $$VLIBS_DIR/{{vlib_name}}/{{item}} {% endfor %}
}
# {{vlib_name}}.pri
#========================================================================================

