#========================================================================================
# vlog_qt.pri
#========================================================================================


#========================================================================================
isEmpty(qi_vlog_qt) {
    qi_vlog_qt = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #   NB! Вычищен руками, оставлена только базовая часть. Файловые логгеры подключаются
    #       через include( $$VLIBS_DIR/vlog/vfilelog.pri )

    include( $$VLIBS_DIR/vlog/vlog.pri )

    HEADERS     += $$VLIBS_DIR/vlog/vlog_qt.h
    SOURCES     += $$VLIBS_DIR/vlog/vlog_qt.cpp

    #>>> Stop your code here ------------------------------------------------------------

}
# vlog_qt.pri
#========================================================================================
