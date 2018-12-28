#========================================================================================
# vsyssignal.pri
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
isEmpty(qi_vsyssignal) {
    qi_vsyssignal = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vsyssignal appended ===")

    isEmpty(VLIBS_DIR): error("vsyssignal: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    CONFIG *= c++11
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vsyssignal


    HEADERS     += $$VLIBS_DIR/vsyssignal/vsyssignal.h

    SOURCES     += $$VLIBS_DIR/vsyssignal/vsyssignal.cpp
}
# vsyssignal.pri
#========================================================================================
