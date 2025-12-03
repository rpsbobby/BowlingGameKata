//
// Created by robert on 11/23/25.
//

#include <array>

#include "Frame.hpp"
#include "gtest/gtest.h"

struct InvalidFrameCase {
    std::array<int, 2> rolls;
};

class InvalidFrameTests : public testing::TestWithParam<InvalidFrameCase> {};

TEST_P(InvalidFrameTests, should_throw_on_invalid_args) {
    const auto &tc = GetParam();
    EXPECT_THROW(Frame(tc.rolls[0], tc.rolls[1]), std::invalid_argument);
}

static const InvalidFrameCase invalid_cases[] = {
        {{10, 1}}, {{1, 10}}, {{-1, -1}}, {{11, 11}}, {{-1, 11}},
};

INSTANTIATE_TEST_SUITE_P(InvalidCases, InvalidFrameTests, ::testing::ValuesIn(invalid_cases));
