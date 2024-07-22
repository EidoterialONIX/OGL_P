cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(ogl_p)

add_executable(ogl_p src/main.cpp)

add_subdirectory(external/glad)
target_link_libraries(ogl_p glad)

add_subdirectory(external/glfw)
target_link_libraries(ogl_p glfw)