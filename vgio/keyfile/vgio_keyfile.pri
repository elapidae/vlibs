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
    isEmpty(qi_not_print_pri_messages): message("=== vgio::keyfile appended ===")

    isEmpty(VLIBS_DIR): error("vgio_keyfile: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vgio/core/impl/vgio_helpers.pri )
    include( $$VLIBS_DIR/vgio/error/vgio_error.pri )

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
