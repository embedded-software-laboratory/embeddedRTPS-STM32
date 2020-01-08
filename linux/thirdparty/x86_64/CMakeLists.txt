# eProsima FastRTPS
option(THIRDPARTY "" ON)
add_subdirectory(thirdparty/Fast-RTPS/ EXCLUDE_FROM_ALL)

file(GLOB OS_DRIVER_SRC "os/*.cpp" )
add_library(asoa_os_driver STATIC ${OS_DRIVER_SRC})
target_link_libraries(asoa_os_driver)

file(GLOB RTPS_DRIVER_SRC "rtps/*.cpp")
add_library(asoa_rtps_driver STATIC ${RTPS_DRIVER_SRC})
target_link_libraries(asoa_rtps_driver asoa_os_driver fastrtps fastcdr)
