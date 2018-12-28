#========================================================================================
# vgpioleg.pri
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
isEmpty(qi_vgpioleg) {
    qi_vgpioleg = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgpioleg appended ===")

    isEmpty(VLIBS_DIR): error("vgpioleg: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vcat/vcat.pri )
    include( $$VLIBS_DIR/vfile/vfile.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vgpioleg


    HEADERS     += $$VLIBS_DIR/vgpioleg/vgpioleg.h

    SOURCES     += $$VLIBS_DIR/vgpioleg/vgpioleg.cpp
}
# vgpioleg.pri
#========================================================================================
