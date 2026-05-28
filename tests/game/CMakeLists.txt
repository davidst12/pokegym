include(GoogleTest)

add_executable(math_test
    math_test.cpp
)

target_link_libraries(math_test
    PRIVATE
        pokegym_lib
        gtest_main
)

gtest_discover_tests(math_test)
