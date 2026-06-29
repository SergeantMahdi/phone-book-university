cmake_minimum_required(VERSION 3.23)
project(
    PhonBook 
    VERSION 1.0.0
    LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor)
add_subdirectory(gui)
add_subdirectory(app)