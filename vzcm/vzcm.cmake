#========================================================================================
# vzcm.cmake
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

if ( NOT  VZCM_INCLUDED )
    set ( VZCM_INCLUDED TRUE )

    message( "Include vzcm..." )


    #<<< Start your code here -----------------------------------------------------------    
    include( "${VLIBS_DIR}/vsignal/vsignal.cmake" )

    find_library( ZCM_LIB name zcm
                    PATHS
                        /usr/lib
                        /usr/local/lib )
    set( V_LIBRARIES ${V_LIBRARIES} ${ZCM_LIB} )
    #>>> Stop your code here ------------------------------------------------------------


    include_directories( "${VLIBS_DIR}/vzcm/")    
    set(V_HEADERS ${V_HEADERS} "${VLIBS_DIR}/vzcm/vzcm_subscriber.h") 

    message( "vzcm included" )

endif()
# vzcm.cmake
#========================================================================================
