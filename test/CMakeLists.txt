cmake_minimum_required(VERSION 3.10)

set(This weighterm_tests)

set(Sources
        ./weighterm_cli_test.cpp
    )

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    gmock
    weighterm_lib
)

add_test(
    NAME ${This}
    COMMAND ${This}
)


include_directories(
    .
    ../libs/googletest/googlemock/include
)
