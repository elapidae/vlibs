#========================================================================================
# vimagewidget.pri
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
isEmpty(qi_vimagewidget) {
    qi_vimagewidget = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vimagewidget appended ===")

    isEmpty(VLIBS_DIR): error("vimagewidget: Need VLIBS_DIR correct path.")


    #<<< Start your code here -----------------------------------------------------------
    #>>> Stop your code here ------------------------------------------------------------

    INCLUDEPATH += $$VLIBS_DIR/vimagewidget

    
    HEADERS     += $$VLIBS_DIR/vimagewidget/vimagewidget.h 
    
    SOURCES     += $$VLIBS_DIR/vimagewidget/vimagewidget.cpp 
}
# vimagewidget.pri
#========================================================================================
