cmake_minimum_required(VERSION 3.26)
project(OpenGlSdl)
set(CMAKE_C_STANDARD 17)


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(OpenGlSdl ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
include_directories(headers)


add_executable(OpenGlSdl src/main.c
        src/OpenGL.c
        headers/OpenGL.h
        src/Shaders.c
        headers/Shaders.h
        headers/File.h
        src/File.c
        headers/Std.h
        src/Std.c
        src/Random.c
        headers/Random.h
        src/Log.c
        headers/Log.h)

target_link_libraries(OpenGlSdl ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_custom_command(
        TARGET OpenGlSdl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders)
