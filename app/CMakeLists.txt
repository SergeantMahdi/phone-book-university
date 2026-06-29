set(APP_NAME App)
set(APP_CORE Core)

add_executable(${APP_NAME}
    main.cpp
)

add_library(${APP_CORE} STATIC 
    src/phoneBook.cpp 
    src/phoneBook.hpp
)

target_link_libraries(${APP_NAME} PRIVATE
    Gui ${APP_CORE}
)