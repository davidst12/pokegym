add_library(battle_engine_lib)
add_library(BattleEngine::battle_engine_lib ALIAS battle_engine_lib)

target_sources(battle_engine_lib
    PRIVATE
        src/pokemon/Pokemon.cpp
        src/pokemon/Move.cpp
        src/trainer/Trainer.cpp
        src/trainer/RandomActionSelector.cpp
        src/battle/Battle.cpp
        src/battle/BattleEngine.cpp
        src/battle/DamageCalculator.cpp
)

target_include_directories(battle_engine_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(battle_engine_lib
    PUBLIC
)
