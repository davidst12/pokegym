add_library(pokegym_lib)

target_sources(pokegym_lib
    PRIVATE
        src/math.cpp
)

target_include_directories(pokegym_lib
    PUBLIC
        include
)

add_executable(pokegym)

target_sources(pokegym
    PRIVATE
        main.cpp
)

target_link_libraries(pokegym
    PRIVATE
        pokegym_lib
)