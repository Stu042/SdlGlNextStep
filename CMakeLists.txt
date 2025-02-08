cmake_minimum_required(VERSION 3.26)
project(SdlGlNextStep)
set(CMAKE_C_STANDARD 11)


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL2)
set(SDL2_SHARED OFF)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${CMAKE_PROJECT_NAME} ${SDL2_BINARY_DIR}/include ${GLEW_INCLUDE_DIRS})
include_directories(headers)


add_executable(${CMAKE_PROJECT_NAME} src/main.c
        src/OpenGL.c
        src/Shaders.c
        src/File.c
        src/Std.c
        src/Random.c
        src/Log.c)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders)


# workaround, copy dlls manually here
if (WIN32)
    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SDL2_BINARY_DIR}/SDL2d.dll
            ${CMAKE_CURRENT_BINARY_DIR}/SDL2d.dll)
endif ()
