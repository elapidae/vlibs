#========================================================================================
# vpid.pri
#
#
# NB! Этот файл правлен руками, постарайтесь не регенерировать.
#
#   Устаревший класс, будет перенесен в VApplication.
#
#========================================================================================


#========================================================================================
isEmpty(qi_vpid) {
    qi_vpid = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vpid appended ===")

    isEmpty(VLIBS_DIR): error("Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vlog/vlog.pri )
    include( $$VLIBS_DIR/vdir/vdir.pri )
    include( $$VLIBS_DIR/voutfile/voutfile.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vpid

    
    HEADERS     += $$VLIBS_DIR/vpid/vpid_saver.h 
    
    SOURCES     += $$VLIBS_DIR/vpid/vpid_saver.cpp 
}
# vpid.pri
#========================================================================================
