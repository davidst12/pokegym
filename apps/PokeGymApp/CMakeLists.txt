add_executable(pokegym)

target_sources(pokegym
    PRIVATE
        main.cpp
)

target_link_libraries(pokegym
    PRIVATE
        BattleEngine::battle_engine_lib
        BattleRenderer::battle_renderer_lib
)