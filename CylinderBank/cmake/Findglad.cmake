if(NOT glad_FOUND)
    include(FetchContent)

    # download and configure the glad project
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    )
    FetchContent_MakeAvailable(glad)
    FetchContent_GetProperties(glad)
    target_link_libraries(
        glad PUBLIC
        ${CMAKE_DL_LIBS}
    )
    if(NOT glad_POPULATED)
        FetchContent_Populate(glad)
        set(GLAD_PROFILE "core") #OpenGL profile
        set(GLAD_API "gl=4.6")   #OpenGL version
        set(GLAD_GENERATOR "c")  #language bindings
        add_subdirectory(
            ${glad_SOURCE_DIR}
            ${glad_BINARY_DIR}
        )
    endif()
endif()
