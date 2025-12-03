cmake_minimum_required(VERSION 3.31.6)
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
        src/frame_counter.cpp
        src/frame_counter.hpp
        src/bonus.cpp
        src/bonus.hpp
        src/errors.hpp
)
target_include_directories(bowling_game PUBLIC src)

# --------------------------
# Tests
# --------------------------
add_executable(bowling_tests
        test/test_frame.cpp
        test/test_frame_counter.cpp
        test/test_bonus.cpp
        test/tests_utils.hpp
        test/test_frame_counter_bonus.cpp
        test/test_frame_counter_completeness.cpp
        test/test_bonus_ctor.cpp
        test/test_frame_spare.cpp
        test/test_frame_invalid.cpp
        test/test_frame_counter_completeness_bonus.cpp
        test/test_frame_counter_scoring.cpp
        test/test_frame_counter_scoring_freestanding.cpp
        test/test_fuzz_valid.cpp
        test/test_fuzz_invalid.cpp
        test/random_fuzz_utils.hpp
)

target_link_libraries(bowling_tests
        PRIVATE
        bowling_game
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(bowling_tests)
