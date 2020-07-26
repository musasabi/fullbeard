file(
    GLOB cpp_source
    "*.cpp"
)

add_library(
    CylinderBank STATIC
    ${cpp_source}
)

target_precompile_headers(
    CylinderBank PRIVATE
    "CylinderBank_pch.hpp"
)

target_include_directories(
    CylinderBank PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendor/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/examples
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

target_compile_options(
    CylinderBank PRIVATE
    -Werror -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors
    -fdiagnostics-color=always
)

set_target_properties(
    CylinderBank PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/CylinderBank
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/CylinderBank
)
