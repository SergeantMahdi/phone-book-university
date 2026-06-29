set(APP_NAME App)
set(APP_LOGIC Logic)

add_executable(${APP_NAME}
    main.cpp
)

add_library(${APP_LOGIC} STATIC 
    src/phoneBook.cpp 
    src/phoneBook.hpp
)

target_link_libraries(${APP_NAME} PRIVATE
    Gui ${APP_LOGIC}
)