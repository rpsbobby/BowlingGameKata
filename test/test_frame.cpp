//
// Created by robert on 11/20/25.
//
#include <array>
#include <gtest/gtest.h>
#include "Frame.hpp"

// ---------------------------------------------
// INVALID CASES
// ---------------------------------------------

struct InvalidFrameCase {
    std::array<int, 2> rolls;
};

class InvalidFrameTests : public ::testing::TestWithParam<InvalidFrameCase> {
};

TEST_P(InvalidFrameTests, should_throw_on_invalid_args) {
    const auto &tc = GetParam();
    EXPECT_THROW(Frame(tc.rolls[0], tc.rolls[1]), std::invalid_argument);
}

static const InvalidFrameCase invalid_cases[] = {
    {{10, 1}},
    {{1, 10}},
    {{-1, -1}},
    {{11, 11}},
    {{-1, 11}},
};

INSTANTIATE_TEST_SUITE_P(
    InvalidCases,
    InvalidFrameTests,
    ::testing::ValuesIn(invalid_cases)
);

// ---------------------------------------------
// BASIC VALID TESTS
// ---------------------------------------------

TEST(Frame, should_create_valid_frame) {
    Frame frame{4, 3};
    ASSERT_EQ(frame.total(), 7);
}

TEST(Frame, should_create_valid_strike) {
    Frame frame{10};
    ASSERT_EQ(frame.total(), 10);
}

TEST(Frame, should_return_strike) {
    Frame frame{10};
    ASSERT_TRUE(frame.is_strike());
}

// ---------------------------------------------
// SPARE CASES
// ---------------------------------------------

struct SpareTestCase {
    std::array<int, 2> rolls;
    bool expected_spare;
};

class SpareTests : public ::testing::TestWithParam<SpareTestCase> {
};

TEST_P(SpareTests, should_return_valid_spare) {
    const auto &tc = GetParam();
    Frame frame{tc.rolls[0], tc.rolls[1]};
    EXPECT_EQ(frame.is_spare(), tc.expected_spare);
}

static const SpareTestCase spare_cases[] = {
    {{1, 9}, true},
    {{5, 5}, true},
    {{3, 4}, false},
    {{0, 10}, true},
    {{10, 0}, false}, // strike, not spare
};

INSTANTIATE_TEST_SUITE_P(
    SpareCases,
    SpareTests,
    ::testing::ValuesIn(spare_cases)
);
