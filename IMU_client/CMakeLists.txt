cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(IMU_MULTIPLEXER VERSION 1.0)

add_library(multiplexerlib STATIC lib/i2c_multiplexer.c)
target_include_directories(multiplexerlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)

add_library(imulib STATIC lib/i2c_bno055.c)
target_include_directories(imulib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(client_IMU client_IMU.cpp)
target_link_libraries(client_IMU PUBLIC pthread boost_system multiplexerlib imulib ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})



