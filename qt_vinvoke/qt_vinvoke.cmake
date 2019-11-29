if ( NOT  VINVOKE_INCLUDED )
    set ( VINVOKE_INCLUDED TRUE )

    message( "Include qt_vinvoke..." )

    include_directories( "${VLIBS_DIR}/qt_vinvoke/")

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/qt_vinvoke/qt_vinvoke.h")
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/qt_vinvoke/qt_vinvoke.cpp")

    message( "qt_vinvoke included" )

endif()
