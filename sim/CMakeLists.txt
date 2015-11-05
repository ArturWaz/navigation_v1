

add_library(sim SimulationEnvironment.cpp SimulationEnvironment.h Timer.h)
target_link_libraries(sim boost_system boost_timer)
