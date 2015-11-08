
file(GLOB filesList *.cpp *.h)


add_library(realLidar ${filesList})
target_link_libraries(realLidar lidar)
