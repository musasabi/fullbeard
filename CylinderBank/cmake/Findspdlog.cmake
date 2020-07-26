include(FindPackageHandleStandardArgs)

find_path(
    spdlog_INCLUDE_DIR
    spdlog/spdlog.h
)

find_library(
    spdlog_LIBRARY
    NAMES spdlog
)

if(EXISTS ${spdlog_INCLUDE_DIR})
    find_package_handle_standard_args(
        spdlog DEFAULT_MSG
        spdlog_INCLUDE_DIR
        spdlog_LIBRARY
    )
endif()

if(spdlog_FOUND)
    set(spdlog_INCLUDE_DIRS ${spdlog_INCLUDE_DIR} )
    set(spdlog_LIBRARIES ${spdlog_LIBRARY} )

else()
    message(STATUS "Pulling in external spdlog")

    include(FetchContent)

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.7.0
    )
    FetchContent_MakeAvailable(spdlog)
    FetchContent_GetProperties(spdlog)

    target_compile_definitions(
        spdlog PUBLIC
        SPDLOG_FMT_EXTERNAL
    )

    target_include_directories(
        spdlog PRIVATE
        ${fmt_INCLUDE_DIRS}
    )

    target_link_libraries(
        spdlog PRIVATE
        fmt
    )

    if(NOT spdlog_POPULATED)
        FetchContent_Populate(spdlog)

        add_subdirectory(
            ${spdlog_SOURCE_DIR}
            ${spdlog_BINARY_DIR}
        )
    endif()

endif()
