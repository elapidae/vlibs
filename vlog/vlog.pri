#========================================================================================
# vlog.pri
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
isEmpty(qi_vlog) {
    qi_vlog = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vlog appended ===")

    isEmpty(VLIBS_DIR): error("vlog: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #   NB! Вычищен руками, оставлена только базовая часть. Файловые логгеры подключаются
    #       через include( $$VLIBS_DIR/vlog/vfilelog.pri )

    include( $$VLIBS_DIR/vcat/vcat.pri )
    include( $$VLIBS_DIR/vchrono/vchrono.pri )

    INCLUDEPATH += $$VLIBS_DIR/vlog
    
    HEADERS     += $$VLIBS_DIR/vlog/vlog.h 
    HEADERS     += $$VLIBS_DIR/vlog/vlog_pretty.h

    HEADERS     += $$VLIBS_DIR/vlog/verror.h
    SOURCES     += $$VLIBS_DIR/vlog/verror.cpp

    HEADERS     += $$VLIBS_DIR/vlog/vlogger.h
    SOURCES     += $$VLIBS_DIR/vlog/vlogger.cpp

    HEADERS     += $$VLIBS_DIR/vlog/vlogentry.h
    SOURCES     += $$VLIBS_DIR/vlog/vlogentry.cpp

    #>>> Stop your code here ------------------------------------------------------------

}
# vlog.pri
#========================================================================================
