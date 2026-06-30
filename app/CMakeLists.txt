set(APP_NAME App)
set(APP_CORE Core)

add_executable(${APP_NAME}
    main.cpp
)

add_library(${APP_CORE} STATIC 
    src/phoneBook.cpp 
    src/phoneBook.hpp
    src/contact.hpp
    src/contact.cpp
)

target_link_libraries(${APP_NAME} PRIVATE
    Gui ${APP_CORE} opengl32
)

target_include_directories(${APP_CORE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)