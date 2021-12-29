cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

set(EXECUTABLE_NAME "DB_GUI_Kluczka")
project(DB_PROJECT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# SFML
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "" FORCE)
set(SFML_USE_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/SFML")

# imgui
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/imgui")

# imgui-sfml
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/lib/imgui/imgui")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/imgui-sfml")

# libpqxx
set(SKIP_BUILD_TEST ON CACHE BOOL "" FORCE)
set(BUILD_DOC OFF CACHE BOOL "" FORCE)
set(INSTALL_TEST OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/libpqxx")


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
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include")

if(CMAKE_HOST_WIN32)
    target_link_options(${EXECUTABLE_NAME}
        PRIVATE
            "-static"
            "-Wl,-Bdynamic"
            "-lopengl32"
            "-lcomdlg32"
            "-lole32"
            "-Wl,-Bstatic")
elseif(CMAKE_HOST_UNIX)
    target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE
            GL
            pq)
else()
    message(STATUS "Unknown system")
endif()

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE sfml-system
            sfml-window
            sfml-graphics
            IMGUI
            ImGui-SFML
            pthread
            pqxx)

if(CMAKE_BUILD_TYPE MATCHES Release
AND CMAKE_COMPILER_IS_GNUCXX
AND CMAKE_HOST_WIN32)
    target_link_options(${EXECUTABLE_NAME}
        PRIVATE
            "-Wl,-subsystem,windows")
endif()
