

isEmpty(qi_vimagewidget) {
    qi_vimagewidget = 1;
    isEmpty(qi_not_print_pri_messages): message("=== VImageWidget appending... ===")

    isEmpty(VLibs_Dir): error("Need to have var VLibs_Dir")

    QT *= opengl

    INCLUDEPATH += $$VLibs_Dir/vimagewidget
    
    HEADERS     += $$VLibs_Dir/vimagewidget/vimagewidget.h
    SOURCES     += $$VLibs_Dir/vimagewidget/vimagewidget.cpp

} # isEmpty(qi_basler_wrap_with_qt)
