add_executable(
    Sandbox
    Sandbox.cpp
)

if(UNIX)
    target_compile_options(
        Sandbox PRIVATE
        -Werror -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors
        -fdiagnostics-color=always
    )
endif()

if(WIN32)
    target_compile_options(
        Sandbox PRIVATE
        /W4
    )
endif()

set_target_properties(
    Sandbox PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(
    Sandbox
    CylinderBank
)