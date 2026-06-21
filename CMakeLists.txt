cmake_minimum_required(VERSION 3.20)
project(
    Pokemon-gym
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
    )
endif()

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

if(ENABLE_COVERAGE)
    add_compile_options(
        -O0
        -g
        --coverage
    )

    add_link_options(--coverage)
endif()

add_subdirectory(third_party)
add_subdirectory(pokegym)

option(POKEGYM_BUILD_TESTS "Build tests" ON)

if(POKEGYM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
