file(
    GLOB cpp_source
    "*.cpp"
)

add_library(
    Fullbeard SHARED
    ${cpp_source}
)

target_precompile_headers(
    Fullbeard PRIVATE
    "fullbeard_pch.hpp"
)

target_include_directories(
    Fullbeard PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    Fullbeard
    ${CMAKE_THREAD_LIBS_INIT}
    fmt
    spdlog
    OpenGL::GL
    glfw
)

target_compile_options(
    Fullbeard PRIVATE
    -Werror -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors
    -fdiagnostics-color=always
)

target_compile_definitions(
    Fullbeard PUBLIC
    SPDLOG_FMT_EXTERNAL
)

set_target_properties(
    Fullbeard PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/Fullbeard
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/Fullbeard
)