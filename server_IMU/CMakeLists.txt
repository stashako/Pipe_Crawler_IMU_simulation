cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SERVER_TEST VERSION 1.0)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(serverlib STATIC lib/IMU_server.cpp)
target_include_directories(serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
target_link_libraries(serverlib PUBLIC pthread ${Boost_INCLUDE_DIR})
#target_link_libraries(serverlib PUBLIC pthread boost_system)


add_executable(main main.cpp)

target_link_libraries(main PUBLIC pthread ${Boost_LIBRARIES} serverlib)