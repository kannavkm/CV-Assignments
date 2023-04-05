cmake_minimum_required(VERSION 3.18)
project(a0)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(q1_a q1_a.cpp)
add_executable(q1_b q1_b.cpp)
add_executable(q2 q2.cpp)
add_executable(q3 q3.cpp)
target_link_libraries(q1_a ${OpenCV_LIBS})
target_link_libraries(q1_b ${OpenCV_LIBS})
target_link_libraries(q2 ${OpenCV_LIBS})
target_link_libraries(q3 ${OpenCV_LIBS})