include(FindPackageHandleStandardArgs)

find_path(
    glfw3_INCLUDE_DIR
    GLFW/glfw3.h
)

find_library(
    glfw3_LIBRARY
    NAMES glfw
)

if(EXISTS ${glfw3_INCLUDE_DIR})
    find_package_handle_standard_args(
        glfw3 DEFAULT_MSG
        glfw3_INCLUDE_DIR
        glfw3_LIBRARY
    )
endif()

if(NOT glfw3_FOUND)
    message(STATUS "Pulling in external GLFW")

    include(FetchContent)

    FetchContent_Declare(
        glfw3
        GIT_REPOSITORY https://github.com/glfw/glfw.git
    )
    FetchContent_MakeAvailable(glfw3)
    FetchContent_GetProperties(glfw3)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    if(NOT glfw3_POPULATED)
        FetchContent_Populate(glfw3)

        add_subdirectory(
            ${glfw3_SOURCE_DIR}
            ${glfw3_BINARY_DIR}
        )
    endif()

endif()
