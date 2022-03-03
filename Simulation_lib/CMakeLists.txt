cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SIM_TEST VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_library(sim_lib STATIC lib/sim.cpp)
target_include_directories(sim_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
target_link_libraries(sim_lib PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})



add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} sim_lib)



