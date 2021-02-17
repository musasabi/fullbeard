file(
    GLOB_RECURSE library_source
    "${CMAKE_CURRENT_SOURCE_DIR}/../*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/glad.c"
)

add_library(
    CylinderBank STATIC
    ${library_source}
)

target_precompile_headers(
    CylinderBank PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/cb_pch.hpp>"
)

target_include_directories(
    CylinderBank PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/CylinderBank
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glm_SOURCE_DIR}
)

target_link_libraries(
    CylinderBank
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    OpenGL::GL
    glfw
    fmt
    spdlog
    imgui
)

target_compile_definitions(
    CylinderBank PUBLIC
    SPDLOG_FMT_EXTERNAL
)

set_source_files_properties(
    "${CMAKE_CURRENT_SOURCE_DIR}/glad.c" PROPERTIES
    COMPILE_FLAGS "-w"
)

if(UNIX)
    target_compile_options(
        CylinderBank PRIVATE
        -Werror -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors
        -fdiagnostics-color=always
    )
endif()

if(MSVC)
    target_compile_options(
        CylinderBank PRIVATE
        /W4
    )
endif()

set_target_properties(
    CylinderBank PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/CylinderBank
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/CylinderBank
)
