#========================================================================================
# vrandom.cmake
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

if ( NOT  VRANDOM_INCLUDED )
    set ( VRANDOM_INCLUDED TRUE )

    message( "Include vrandom..." )

    #<<< Start your code here -----------------------------------------------------------
    include( "${VLIBS_DIR}/c++11/c++11.cmake" )
    include( "${VLIBS_DIR}/vchrono/vchrono.cmake" )
    #>>> Stop your code here ------------------------------------------------------------

    include_directories( "${VLIBS_DIR}/vrandom/")

    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vrandom/vrandom.h") 
    
    set(V_SOURCES ${V_SOURCES} "${VLIBS_DIR}/vrandom/vrandom.cpp") 

    message( "vrandom included" )

endif()
# vrandom.cmake
#========================================================================================
