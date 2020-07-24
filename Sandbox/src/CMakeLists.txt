add_executable(
    Sandbox
    Sandbox.cpp
)

target_compile_options(
    Sandbox PRIVATE
    -Werror -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors
)

set_target_properties(
    Sandbox PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(
    Sandbox
    Fullbeard
)