

isEmpty(qt_pretty_build) {
    qt_pretty_build = 1;
    isEmpty(qi_not_print_pri_messages): message("=== qt_pretty_build appended ===")


    # каталог, куда загонять результирующий исполняемый файл
    DESTDIR = bin

    # промежуточные файлы, созданные moc
    MOC_DIR = moc

    # объектные файлы
    OBJECTS_DIR = obj

    # промежуточные файлы, созданные компилятором
    # ресурсов Qt (rcc)
    RCC_DIR = rcc

    # промежуточные файлы, созданные компилятором
    # файлов форм (.ui) Qt (uic)
    UI_DIR = uic
}


