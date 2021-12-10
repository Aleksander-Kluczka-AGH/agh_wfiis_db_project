cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

set(EXECUTABLE_NAME "main")
project(DB_PROJECT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# SFML
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_USE_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/SFML")

# imgui
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/imgui")

# imgui-sfml
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/lib/imgui/imgui")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/imgui-sfml")


file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${EXECUTABLE_NAME})

target_compile_options(${EXECUTABLE_NAME}
    PRIVATE
        "-Wall"
        "-Wextra"
        "-pedantic")

target_compile_features(${EXECUTABLE_NAME}
    PRIVATE
        "cxx_std_20")

target_sources(${EXECUTABLE_NAME}
    PRIVATE
        ${SOURCES}
        "main.cpp")

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE sfml-system
            sfml-window
            sfml-graphics
            IMGUI
            ImGui-SFML)

if(CMAKE_HOST_WIN32)
    target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE opengl32
            comdlg32
            ole32)
elseif(CMAKE_HOST_UNIX)
    target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE GL)
else()
    message(STATUS "Unknown system")
endif()