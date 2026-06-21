include(GoogleTest)

add_executable(battle_engine_test
    BattleEngineTest.cpp
)

target_link_libraries(battle_engine_test
    PRIVATE
        pokegym_lib
        gtest_main
)

gtest_discover_tests(battle_engine_test)
