

isEmpty(qt_pretty_build_for_tests) {
    qt_pretty_build_for_tests = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qt_pretty_build_for_tests ===")

#    system()
    VTEST_BUILD_DIR = ../test_builds

    # каталог, куда загонять результирующий исполняемый файл
    DESTDIR = $$VTEST_BUILD_DIR/$$TARGET

    # промежуточные файлы, созданные moc
    MOC_DIR = $$VTEST_BUILD_DIR/$$TARGET/moc

    # объектные файлы
    OBJECTS_DIR = $$VTEST_BUILD_DIR/$$TARGET/obj

    # промежуточные файлы, созданные компилятором
    # ресурсов Qt (rcc)
    RCC_DIR = $$VTEST_BUILD_DIR/$$TARGET/rcc

    # промежуточные файлы, созданные компилятором
    # файлов форм (.ui) Qt (uic)
    UI_DIR = $$VTEST_BUILD_DIR/$$TARGET/uic
}


