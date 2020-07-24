# 3.16 is required for precompiled headers
cmake_minimum_required(VERSION 3.16)

project(
    Fullbeard
    VERSION 0.1.0
    DESCRIPTION "A follow-along of the Hazel engine by TheCherno"
    LANGUAGES CXX
)

find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(src)

    export(
        TARGETS Fullbeard
        FILE ${PROJECT_SOURCE_DIR}/FullbeardConfig.cmake
    )
endif()
