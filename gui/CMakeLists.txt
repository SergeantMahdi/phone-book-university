set(LIBRARY_NAME Gui)

add_library(${LIBRARY_NAME} STATIC
    src/gui.cpp
    src/gui.hpp
)

# Expose this folder's header files to the rest of the project
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${LIBRARY_NAME} PUBLIC
    imgui Logic
)