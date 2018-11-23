

isEmpty(qt_pretty_build_for_tests) {
    qt_pretty_build_for_tests = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qt_pretty_build_for_tests ===")

#    system()

    # каталог, куда загонять результирующий исполняемый файл
    DESTDIR = ../builds/$$TARGET

    # промежуточные файлы, созданные moc
    MOC_DIR = ../builds/$$TARGET/moc

    # объектные файлы
    OBJECTS_DIR = ../builds/$$TARGET/obj

    # промежуточные файлы, созданные компилятором
    # ресурсов Qt (rcc)
    RCC_DIR = ../builds/$$TARGET/rcc

    # промежуточные файлы, созданные компилятором
    # файлов форм (.ui) Qt (uic)
    UI_DIR = ../builds/$$TARGET/uic
}


