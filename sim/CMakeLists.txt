
file(GLOB filesList *.cpp *.h)


add_library(sim ${filesList})
target_link_libraries(sim boost_system boost_timer)
