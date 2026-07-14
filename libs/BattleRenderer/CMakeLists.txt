add_library(battle_renderer_lib)
add_library(BattleRenderer::battle_renderer_lib ALIAS battle_renderer_lib)

target_sources(battle_renderer_lib
    PRIVATE
        src/console/ConsoleBattleRenderer.cpp
        src/console/ConsoleActionSelector.cpp
        src/sdl/SdlActionSelector.cpp
        src/sdl/SdlBattleRenderer.cpp
)

target_include_directories(battle_engine_lib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(battle_renderer_lib
    PUBLIC
        BattleEngine::battle_engine_lib
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
        SDL2_image::SDL2_image
)
