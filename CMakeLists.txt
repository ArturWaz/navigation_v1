cmake_minimum_required(VERSION 2.8)



#set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.4.1\\5.4\\mingw491_32")
#set(CMAKE_PREFIX_PATH CMAKE_PREFIX_PATH "C:\\boost\\")
#set(CMAKE_PREFIX_PATH CMAKE_PREFIX_PATH "F:\\_compilers\\_lib\\opencv\\build")


set(PROJECT_NAME simulation)
project(${PROJECT_NAME})


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_SHARED_LINKER_FLAGS "-static")
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif (NOT MSVC)
if (UNIX)
    set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
endif (UNIX)


#find_package(OpenCV REQUIRED)

include_directories("sim" "lidar" "sim/realLidar")

add_subdirectory(sim)
add_subdirectory(lidar)
add_subdirectory(sim/realLidar)

set(LIBS boost_system boost_timer sim lidar realLidar)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBS})




if (1)
    enable_testing()
    
    file(GLOB_RECURSE testsList test___*.cpp)
    foreach(i IN LISTS testsList)
        string(REPLACE "/" ";" iL ${i})
        list(GET iL -1 file)
        string(REPLACE ".cpp" "" file ${file})
        project(${file})
        add_executable(${file} ${i})
        target_link_libraries(${file} boost_unit_test_framework ${LIBS})
        add_test(${file} ${file})
    endforeach()
endif()

