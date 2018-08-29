#========================================================================================
# keyfile.pri
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
isEmpty(qi_vgio_keyfile) {
    qi_vgio_keyfile = 1;
    isEmpty(qi_not_print_pri_messages): message("=== keyfile appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vgio/core/impl/helpers.pri )
    include( $$VLIBS_DIR/vgio/error/error.pri )

    INCLUDEPATH += $$VLIBS_DIR/vgio/keyfile

    HEADERS     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.h
    SOURCES     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile.cpp

    HEADERS     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile_schema.h
    SOURCES     += $$VLIBS_DIR/vgio/keyfile/vgio_keyfile_schema.cpp

    OTHER_FILES += $$VLIBS_DIR/vgio/keyfile/README
    #>>> Stop your code here ------------------------------------------------------------

}
# keyfile.pri
#========================================================================================
