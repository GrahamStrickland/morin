cmake_minimum_required(VERSION 3.24)
project(morin
    VERSION 0.0.1
    DESCRIPTION "Numerical solutions and plots for exercises from \"Introduction to Classical Mechanics\" - David Morin"
    HOMEPAGE_URL "https://github/com/GrahamStrickland/morin"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++26 -pedantic -Wall -Wextra -Werror")

set(SOURCES
    src/utils.cpp
    src/p1_7.cpp
    src/ex1_17.cpp
    src/ex1_18.cpp
    src/main.cpp
)

add_executable(morin ${SOURCES})

target_compile_features(morin PUBLIC cxx_std_26)

target_include_directories(morin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
