# GLFW (Windowing library)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# GLAD
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# Build Dear ImGui
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Link libraries

target_link_libraries(imgui PUBLIC glfw glad)

if(UNIX AND NOT APPLE)
    target_link_libraries(imgui PUBLIC dl)
endif()