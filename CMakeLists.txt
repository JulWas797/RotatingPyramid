cmake_minimum_required(VERSION 3.25)
project(RotatingPyramidGL C)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_C_STANDARD 23)

add_executable(RotatingPyramidGL main.c)
target_link_libraries(RotatingPyramidGL ${OPENGL_LIBRARIES})
target_link_libraries(RotatingPyramidGL ${GLUT_LIBRARIES})
target_link_libraries(RotatingPyramidGL -lOpenGL32 -lfreeGLUT)
