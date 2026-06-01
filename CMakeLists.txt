cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(AntiMatter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui")

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(AntiMatterEngine SHARED 
    src/engine/entryPoint/entryPoint.h
    src/engine/entryPoint/entryPoint.cpp
    third_party/glad/src/glad.c
    ${IMGUI_SOURCES}
    src/engine/input/input.cpp
    src/engine/input/input.h
    src/engine/filesystem/filesystem.h
    src/engine/filesystem/filesystem.cpp
    src/engine/audio/miniaudio/miniaudio.h
    src/engine/audio/miniaudio/miniaudio.c
    src/engine/audio/audio.h
    src/engine/audio/audio.cpp
    src/engine/engine.h
    src/engine/debug/Debug.h
    src/engine/debug/Debug.cpp
    src/engine/camera/camera.h
    src/engine/camera/camera.cpp
)

set(glfw3_DIR "/usr/lib/cmake/glfw3/")

target_include_directories(AntiMatterEngine PUBLIC 
    src/engine 
    third_party/imgui
    third_party/imgui/backends
    third_party/glad/include
)

add_executable(AntiMatterGame src/games/reactorGame/main.cpp
    src/games/reactorGame/reactor/reactor.h
    src/games/reactorGame/reactor/reactor.cpp
)

target_include_directories(AntiMatterGame PUBLIC 
    src/engine/
)

target_link_libraries(AntiMatterGame PRIVATE AntiMatterEngine glfw OpenGL::GL glm::glm)

