if ( NOT QCUSTOMPLOT_INCLUDED )
    set ( QCUSTOMPLOT_INCLUDED TRUE )

    message( "Include qcustomplot..." )

    include( "${VLIBS_DIR}/vgeometry/vgeometry.cmake" )

    include_directories( "${VLIBS_DIR}/qcustomplot/")

    set( V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/qcustomplot/qcustomplot.h")
    set( V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/qcustomplot/qcustomplot.cpp")

    message( "qcustomplot included" )

endif()
