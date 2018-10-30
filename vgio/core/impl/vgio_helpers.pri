#========================================================================================
# impl.pri
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
isEmpty(qi_vgio_core_impl) {
    qi_vgio_core_impl = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgio_core_impl appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vgio/core/vgio_core.pri )

    INCLUDEPATH += $$VLIBS_DIR/vgio/core

    HEADERS     += $$VLIBS_DIR/vgio/core/impl/vgio_casting_helper.h

    HEADERS     += $$VLIBS_DIR/vgio/core/impl/vgio_converting_helper.h
    SOURCES     += $$VLIBS_DIR/vgio/core/impl/vgio_converting_helper.cpp
    #>>> Stop your code here ------------------------------------------------------------

}
# impl.pri
#========================================================================================
