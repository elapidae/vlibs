#========================================================================================
# vimage.pri
#   NB! Изменен руками, постарайтесь не перегенерировать.
#========================================================================================


#========================================================================================
isEmpty(qi_vimage) {
    qi_vimage = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimage appended ===")

    isEmpty(VLIBS_DIR): error("vimage: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    include( $$VLIBS_DIR/vsignal/vsignal.pri )
    include( $$VLIBS_DIR/vchrono/vchrono.pri )
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vimage
    
    HEADERS     += $$VLIBS_DIR/vimage/vimage.h
    SOURCES     += $$VLIBS_DIR/vimage/vimage.cpp

    HEADERS     += $$VLIBS_DIR/vimage/abstract_vimage_supplier.h
}
# vimage.pri
#========================================================================================
