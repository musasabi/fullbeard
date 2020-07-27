# 3.16 is required for precompiled headers
cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)
find_package(OpenGL  REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(glad   REQUIRED)
find_package(glfw3  REQUIRED)
find_package(fmt    REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui  REQUIRED)
find_package(glm    REQUIRED)

add_subdirectory(src)

