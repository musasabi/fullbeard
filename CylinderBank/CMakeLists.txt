# 3.16 is required for precompiled headers
cmake_minimum_required(VERSION 3.16)

project(
    CylinderBank
    VERSION 0.1.0
    DESCRIPTION "A follow-along of the Hazel engine by TheCherno"
)

find_package(Threads REQUIRED)
find_package(OpenGL  REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(glad   REQUIRED)
find_package(glfw3  REQUIRED)
find_package(fmt    REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui  REQUIRED)
find_package(glm    REQUIRED)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(src)

    list(APPEND EXPORT_LIBS "glad")

    if(NOT EXISTS ${glfw3_INCLUDE_DIR})
        list(APPEND EXPORT_LIBS "glfw")
    endif()

    if(NOT EXISTS ${fmt_INCLUDE_DIR})
        list(APPEND EXPORT_LIBS "fmt")
    endif()

    if(NOT EXISTS ${spdlog_INCLUDE_DIR})
        list(APPEND EXPORT_LIBS "spdlog")
    endif()

    if(NOT EXISTS ${imgui_INCLUDE_DIR})
        list(APPEND EXPORT_LIBS "imgui")
    endif()

    if(NOT EXISTS ${glm_INCLUDE_DIR})
        list(APPEND EXPORT_LIBS "glm")
    endif()

    export(
        TARGETS CylinderBank ${EXPORT_LIBS}
        FILE ${PROJECT_SOURCE_DIR}/CylinderBankConfig.cmake
    )
endif()
