include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui)

if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    add_subdirectory(
        ${imgui_SOURCE_DIR}
    )
endif()

add_library(
    imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_compile_options(
    imgui PRIVATE
    -DIMGUI_IMPL_OPENGL_LOADER_GLAD # configure GLAD as the loader
)

target_include_directories(
    imgui PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glad_BINARY_DIR}/include # so imgui can find glad
)

target_link_libraries(
    imgui PRIVATE
    glad
    glfw
    ${OPENGL_LIBRARY}
)
