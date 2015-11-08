
file(GLOB filesList *.cpp *.h)


add_library(lidar ${filesList})
#target_link_libraries(lidar boost_system boost_timer)
