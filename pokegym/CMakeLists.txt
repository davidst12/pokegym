add_library(pokegym_lib)

target_sources(pokegym_lib
    PRIVATE
        src/pokemon/Pokemon.cpp
        src/pokemon/Move.cpp
        src/trainer/Trainer.cpp
        src/trainer/RandomActionSelector.cpp
        src/battle/Battle.cpp
        src/battle/BattleEngine.cpp
        src/battle/DamageCalculator.cpp
        src/presentation/ConsoleBattleRenderer.cpp
        src/presentation/ConsoleActionSelector.cpp
        src/presentation/SdlActionSelector.cpp
        src/presentation/SdlBattleRenderer.cpp
)

target_include_directories(pokegym_lib
    PUBLIC
        include
)

target_link_libraries(pokegym_lib
    PUBLIC
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
        SDL2_image::SDL2_image
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