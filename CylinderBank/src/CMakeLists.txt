file(
    GLOB_RECURSE library_source
    "${CMAKE_CURRENT_SOURCE_DIR}/../*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../*.hpp"
)

add_library(
    CylinderBank STATIC
    ${library_source}
)

target_precompile_headers(
    CylinderBank PRIVATE
    "CylinderBank_pch.hpp"
)

target_include_directories(
    CylinderBank PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/examples
    ${glm_SOURCE_DIR}
)

target_link_libraries(
    CylinderBank
    ${CMAKE_THREAD_LIBS_INIT}
    OpenGL::GL
    glad
    glfw
    fmt
    spdlog
    imgui
)

target_compile_definitions(
    CylinderBank PUBLIC
    SPDLOG_FMT_EXTERNAL
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
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/CylinderBank
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/CylinderBank
)
