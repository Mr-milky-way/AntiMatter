cmake_minimum_required(VERSION 3.10.0)
project(AntiMatter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Set a common directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set a common directory for libraries (DLLs on Windows, .so on Linux)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set a common directory for static libraries (.lib on Windows, .a on Linux)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


add_library(AntiMatterEngine SHARED 
    src/engine/app.h
    src/engine/app.cpp
)

set(glfw3_DIR "/usr/lib/cmake/glfw3/")

find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)

target_include_directories(AntiMatterEngine PUBLIC src/engine)

add_executable(AntiMatterGame src/game/main.cpp)

target_link_libraries(AntiMatterGame PRIVATE AntiMatterEngine glfw OpenGL::GL)

