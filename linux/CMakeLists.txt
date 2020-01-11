cmake_minimum_required(VERSION 3.13)
project(embedded_test)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)

add_subdirectory(Fast-RTPS)

add_executable(simple_receiver "src/main.cpp" "src/rtps.cpp")
target_link_libraries(simple_receiver asoa_rtps_driver)

