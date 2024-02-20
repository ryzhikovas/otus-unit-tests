include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        lee_tests
        cell_test.cpp
        map_test.cpp
)
target_link_libraries(
        lee_tests
        lee_impl
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lee_tests)