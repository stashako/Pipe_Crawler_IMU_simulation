cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ASIO_TEST VERSION 1.0)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(server_IMU server_IMU.cpp)
add_executable(async_server_3 async_server_3.cpp)

target_link_libraries(server_IMU PUBLIC pthread ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(async_server_3 PUBLIC pthread ${Boost_LIBRARIES})