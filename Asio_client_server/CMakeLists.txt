cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ASIO_TEST VERSION 1.0)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(client client.cpp)
#add_executable(async_server async_server.cpp)
add_executable(async_server_2 async_server_2.cpp)

target_link_libraries(client PUBLIC pthread ${Boost_LIBRARIES})
#target_link_libraries(async_server PUBLIC pthread ${Boost_LIBRARIES})
target_link_libraries(async_server_2 PUBLIC pthread ${Boost_LIBRARIES})
