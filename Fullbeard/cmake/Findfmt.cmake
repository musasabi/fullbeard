include(FindPackageHandleStandardArgs)

find_path(
    fmt_INCLUDE_DIR
    fmt/core.h
)

find_library(
    fmt_LIBRARY
    NAMES fmt
)

if(EXISTS ${fmt_INCLUDE_DIR})
    find_package_handle_standard_args(
        fmt DEFAULT_MSG
        fmt_INCLUDE_DIR
        fmt_LIBRARY
    )
endif()

if(fmt_FOUND)
    set(fmt_INCLUDE_DIRS ${fmt_INCLUDE_DIR} )
    set(fmt_LIBRARIES ${fmt_LIBRARY} )

    mark_as_advanced(
        fmt_LIBRARY
        fmt_INCLUDE_DIR
        fmt_DIR
    )

else()
    message(STATUS "Pulling in external fmt library")

    include(FetchContent)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    )
    FetchContent_MakeAvailable(fmt)
    FetchContent_GetProperties(fmt)

    if(NOT fmt_POPULATED)
        FetchContent_Populate(fmt)

        add_subdirectory(
            ${fmt_SOURCE_DIR}
            ${fmt_BINARY_DIR}
        )
    endif()

endif()
