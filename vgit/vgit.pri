#========================================================================================
# vgit.pri
#
#http://blog.mgsxx.com/?p=2140
#
#   Это система автоматического подтягивания в плюсовый код информации о текущем коммите.
#
#   Как это реализуется надо обязательно и подробно описать, смысл такой, чтобы скриптами
#   перейти в папку с исходниками, награбить информацию во флаги компиляции и
#   макросами вытянуть их до состояния объектов C++. Короче, магия, в основном, черная.
#
#   UPD 17-08-2018
#   Решена проблема "оторванной головы". Когда реп находится в статусе Detached HEAD,
#   команда git branch выдает "* (HEAD detached at 27130b6)".
#   В результате, awk вытягивает "(HEAD". Скобочка, в итоге, делает больно препроцессору.
#   Юра написал команду sed, чтобы избавиться от этой самой скобочки.
#
#
#========================================================================================


isEmpty(qi_vgit2) {
    qi_vgit2 = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgit2 appended ===")

    isEmpty(Main_Dir): error("vgit2: Please, specify Main_Dir=$$PWD in your .pro file.")


    INCLUDEPATH += $$VLIBS_DIR/vgit
    HEADERS     += $$VLIBS_DIR/vgit/vgit.h
    SOURCES     += $$VLIBS_DIR/vgit/vgit.cpp


    VGIT_REVCOUNT = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git rev-list HEAD --count)"

    VGIT_HASH     = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%H\")"

    VGIT_DATE     = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%ad\")"

    VGIT_AUTHOR   = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%an\")"

    VGIT_BRANCH   = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git branch | awk \'{print \$2}\' \
                    | sed \'s/\(//g\')"



    DEFINES += VGIT_REVCOUNT_ELPD=\"$${VGIT_REVCOUNT}\"
    DEFINES += VGIT_HASH_ELPD=\"$${VGIT_HASH}\"
    DEFINES += VGIT_DATE_ELPD=\"$${VGIT_DATE}\"
    DEFINES += VGIT_AUTHOR_ELPD=\"$${VGIT_AUTHOR}\"
    DEFINES += VGIT_BRANCH_ELPD=\"$${VGIT_BRANCH}\"

    message(">>> Current git hash: $${VGIT_HASH}, \
                             branch: $${VGIT_BRANCH}, \
                             revcount: $${VGIT_REVCOUNT}, \
                             author: $${VGIT_AUTHOR}, \
                             date: $${VGIT_DATE}\
                             ")


    VMAIN_O = $$system_path($$OUT_PWD/$$OBJECTS_DIR/main.o)
    VGIT_O  = $$system_path($$OUT_PWD/$$OBJECTS_DIR/vgit.o)
    VMakeFileForRemove = $$system_path($$OUT_PWD/Makefile)
    QMAKE_POST_LINK  += \
                        $(DEL_FILE) $${VMAIN_O} && \
                        $(DEL_FILE) $${VGIT_O}  && \
                        $(DEL_FILE) $${VMakeFileForRemove}

    #DEFINES += VGIT_CURRENT_GENERAL_SOURCES_PATH=\"$${PWD}\"
    #DEFINES += VGIT_CURRENT_GENERAL_BUILD_PATH=\"$$shadowed($$PWD)\"
}
# vgit.pri
#========================================================================================
