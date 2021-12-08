cmake_minimum_required(VERSION 3.10)

set(This weighterm_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
        ./weighterm_cli_test.cpp
        )

add_executable(${This} ${Sources})
target_link_libraries(${This} gtest_main gmock weighterm_lib)

add_test(
        NAME ${This}
        COMMAND ${This}
)

include_directories(
        .
)
