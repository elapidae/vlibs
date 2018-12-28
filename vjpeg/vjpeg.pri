#========================================================================================
# vjpeg.pri
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
isEmpty(qi_vjpeg) {
    qi_vjpeg = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vjpeg appended ===")

    isEmpty(VLIBS_DIR): error("vjpeg: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vimage/vimage.pri )
    include( $$VLIBS_DIR/vstring/vstring.pri )
    include( $$VLIBS_DIR/voutfile/voutfile.pri )

    LIBS *= -ljpeg
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vjpeg


    HEADERS     += $$VLIBS_DIR/vjpeg/vjpeg.h

    SOURCES     += $$VLIBS_DIR/vjpeg/vjpeg.cpp
}
# vjpeg.pri
#========================================================================================
