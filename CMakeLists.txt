cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set (PROJECT_NAME openglTraining)
project(${PROJECT_NAME})

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "" )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "" )
set( GLFW_INSTALL OFF CACHE BOOL  "" )

add_executable(${PROJECT_NAME} src/main.cpp src/renderer/ShaderProgram.cpp src/renderer/ShaderProgram.h src/stb/stb_image.h src/stb/stb_image.cpp)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)