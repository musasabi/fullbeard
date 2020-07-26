include(FindPackageHandleStandardArgs)

find_path(
    glm_INCLUDE_DIR
    glm/glm.hpp
)

if(EXISTS ${glm_INCLUDE_DIR})
    find_package_handle_standard_args(
        glm DEFAULT_MSG
        glm_INCLUDE_DIR
    )
endif()

if(NOT glm_FOUND)
    message(STATUS "Pulling in external glm")

    include(FetchContent)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
    )
    FetchContent_MakeAvailable(glm)
    FetchContent_GetProperties(glm)

    if(NOT glm_POPULATED)
        FetchContent_Populate(glm)
    endif()

endif()
