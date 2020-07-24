file(
    GLOB cpp_source
    "*.cpp"
)

add_library(
    glad
    ${PROJECT_SOURCE_DIR}/vendor/src/glad.c
)

target_link_libraries(
    glad
    ${CMAKE_DL_LIBS}
)

target_include_directories(
    glad PRIVATE
    ${PROJECT_SOURCE_DIR}/vendor/include
)

add_library(
    Fullbeard STATIC
    ${cpp_source}
)

target_precompile_headers(
    Fullbeard PRIVATE
    "fullbeard_pch.hpp"
)

target_include_directories(
    Fullbeard PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendor/include
)

target_link_libraries(
    Fullbeard
    ${CMAKE_THREAD_LIBS_INIT}
    fmt
    spdlog
    OpenGL::GL
    glfw
    glad
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