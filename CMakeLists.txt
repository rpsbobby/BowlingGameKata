cmake_minimum_required(VERSION 4.1)
project(BowlingGameKata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------
# GoogleTest via FetchContent
# --------------------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --------------------------
# Library under test
# --------------------------
add_library(bowling_game
        src/Frame.cpp
        src/Frame.hpp
        src/bowling_game.cpp
        src/bowling_game.hpp
        src/frame_counter.cpp
        src/frame_counter.hpp
        src/bonus.cpp
        src/bonus.hpp
)
target_include_directories(bowling_game PUBLIC src)

# --------------------------
# Tests
# --------------------------
add_executable(bowling_tests
        test/test_frame.cpp
        test/test_game.cpp
        test/test_frame_counter.cpp
        test/test_bonus.cpp
)

target_link_libraries(bowling_tests
        PRIVATE
        bowling_game
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(bowling_tests)
