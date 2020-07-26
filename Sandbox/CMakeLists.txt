cmake_minimum_required(VERSION 3.16)

project(
    Sandbox
    VERSION 0.1.0
    DESCRIPTION "A follow-along of the Hazel engine (sandbox) by TheCherno"
    LANGUAGES CXX
)

find_package(Threads REQUIRED)
find_package(OpenGL  REQUIRED)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CylinderBank_DIR ${PROJECT_SOURCE_DIR}/../CylinderBank/)
    find_package(CylinderBank REQUIRED)

    add_subdirectory(src)
endif()
