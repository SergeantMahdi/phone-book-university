cmake_minimum_required(VERSION 3.23)
project(
    PhoneBook 
    VERSION 1.0.0
    LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS_DEBUG "/MDd /ZI /Ob0 /Od /RTC1")
endif()

add_subdirectory(vendor)
add_subdirectory(gui)
add_subdirectory(app)