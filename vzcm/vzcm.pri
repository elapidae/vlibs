#========================================================================================
# vzcm.pri
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
isEmpty(qi_vzcm) {
    qi_vzcm = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vzcm appended ===")

    isEmpty(VLIBS_DIR): error("vzcm: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------

    LIBS += -lzcm -L/usr/local/lib
    include( $$VLIBS_DIR/vsignal/vsignal.pri )

    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vzcm
    HEADERS     += $$VLIBS_DIR/vzcm/vzcm_subscriber.h 
    
}
# vzcm.pri
#========================================================================================
