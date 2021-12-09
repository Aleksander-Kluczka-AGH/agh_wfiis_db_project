cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(IMGUI)

set(CMAKE_COLOR_MAKEFILE True)

add_library(IMGUI STATIC)

target_compile_options(IMGUI
    PRIVATE "-Wall"
            "-Wextra"
            "-pedantic"
            "-std=c++20"
)
target_sources(IMGUI PRIVATE "${PROJECT_SOURCE_DIR}/imgui/imgui.cpp")
target_include_directories(IMGUI INTERFACE "${PROJECT_SOURCE_DIR}/imgui")
target_link_libraries(IMGUI PRIVATE m)
