#http://blog.mgsxx.com/?p=2140

isEmpty(qi_vgit2) {
    qi_vgit2 = 1;
    isEmpty(qi_not_print_pri_messages): message("=== vgit2 appended ===")

    isEmpty(Main_Dir): error("Please, specify Main_Dir=$$PWD in your .pro file.")

    #isEmpty(VLibs_Dir): error("Please, specify VLibs_Dir in your .pro file.")
    #include( $$VLibs_Dir/vcat/vcat.pri )

    INCLUDEPATH += $$VLibs_Dir/vgit
    HEADERS     += $$VLibs_Dir/vgit/vgit.h
    SOURCES     += $$VLibs_Dir/vgit/vgit.cpp


    VGIT_REVCOUNT = $$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git rev-list HEAD --count)

    VGIT_HASH     = $$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git log -n 1 --pretty=format:\"%H\")

    VGIT_BRANCH   = $$system(cd \"$$system_path($$Main_Dir)\"    && \
                    git branch | awk \'{print \$2}\')


    DEFINES += VGIT_REVCOUNT_ELPD=\"$${VGIT_REVCOUNT}\"
    DEFINES += VGIT_HASH_ELPD=\"$${VGIT_HASH}\"
    DEFINES += VGIT_BRANCH_ELPD=\"$${VGIT_BRANCH}\"


    message(">>> Current git hash: $${VGIT_HASH}, \
                             branch: $${VGIT_BRANCH}, \
                             revcount: $${VGIT_REVCOUNT}")


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
