cmake_minimum_required(VERSION 3.13)
project(embedded_test)
set(CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_STANDARD 11)

include_directories(include)

include_directories(${PROJECT_SOURCE_DIR}/Fast-RTPS/include)
include_directories(${PROJECT_SOURCE_DIR}/build/Fast-RTPS/include)
add_subdirectory(Fast-RTPS)

add_executable(embedded_rtps_test "src/main.cpp" "src/rtps.cpp")
target_link_libraries(embedded_rtps_test fastrtps)

