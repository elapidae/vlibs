
message( "OpenCV libraries connector..." )


#include_directories("/usr/include/glib-2.0/")

find_package( OpenCV REQUIRED )

include_directories( ${OPENCV_INCLUDE_DIRS} )



#add_executable(${PROJECT} ${SOURCES} ${GTK2_LIBRARIES})
