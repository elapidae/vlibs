#http://blog.mgsxx.com/?p=2140

isEmpty(qi_vgit2) {
    qi_vgit2 = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgit2 appended ===")

    isEmpty(Main_Dir): error("Please, specify Main_Dir=$$PWD in your .pro file.")


    INCLUDEPATH += $$VLibs_Dir/vgit
    HEADERS     += $$VLibs_Dir/vgit/vgit.h
    SOURCES     += $$VLibs_Dir/vgit/vgit.cpp


    VGIT_REVCOUNT = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git rev-list HEAD --count)"

    VGIT_HASH     = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%H\")"

    VGIT_DATE     = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%ad\")"

    VGIT_AUTHOR   = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%an\")"

# Каменный цветочек не выходит, походу из-за кодировки.
#    VGIT_COMMENT  = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
#                    git log -n 1 --pretty=format:\"%s\")"

    VGIT_BRANCH   = "$$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git branch | awk \'{print \$2}\')"


    DEFINES += VGIT_REVCOUNT_ELPD=\"$${VGIT_REVCOUNT}\"
    DEFINES += VGIT_HASH_ELPD=\"$${VGIT_HASH}\"
    DEFINES += VGIT_DATE_ELPD=\"$${VGIT_DATE}\"
    DEFINES += VGIT_AUTHOR_ELPD=\"$${VGIT_AUTHOR}\"
#    DEFINES += VGIT_COMMENT_ELPD=\"$${VGIT_COMMENT}\"
    DEFINES += VGIT_BRANCH_ELPD=\"$${VGIT_BRANCH}\"

    message(">>> Current git hash: $${VGIT_HASH}, \
                             branch: $${VGIT_BRANCH}, \
                             revcount: $${VGIT_REVCOUNT}, \
                             author: $${VGIT_AUTHOR}, \
                             date: $${VGIT_DATE}\
#                             comment: $${VGIT_COMMENT}\
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
