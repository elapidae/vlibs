# Этот CMake файл сгенерирован автоматически.
# Вносить изменения можно между строк   !#<Start your code here" и "#> Stop your code here"
# Все остальные изменения будут перезаписаны.

isEmpty(qi_{{vlib_name}}) {
    qi_{{vlib_name}} = 1;
    isEmpty(qi_not_print_pri_messages): message("=== {{vlib_name}} appended ===")

    isEmpty(VLibs_Dir): error("Need VLibs_Dir correct path.")

    CONFIG *= c++11

    #< Start your code here
{{manual_code}}    #> Stop your code here

    INCLUDEPATH += $$VLibs_Dir/{{vlib_name}}

    {% for item in headers %}
    HEADERS     += $$VLibs_Dir/{{vlib_name}}/{{item}} {% endfor %}
    {% for item in sources %}
    SOURCES     += $$VLibs_Dir/{{vlib_name}}/{{item}} {% endfor %}
}
