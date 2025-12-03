//
// Created by robert on 11/23/25.
//

// ---------------------------------------------
// SPARE CASES
// ---------------------------------------------

#include <array>

#include "Frame.hpp"
#include "gtest/gtest.h"

struct SpareTestCase {
    std::array<int, 2> rolls;
    bool expected_spare;
};

class SpareTests : public testing::TestWithParam<SpareTestCase> {};

TEST_P(SpareTests, should_return_valid_spare) {
    const auto &tc = GetParam();
    Frame frame{tc.rolls[0], tc.rolls[1]};
    EXPECT_EQ(frame.is_spare(), tc.expected_spare);
}

static const SpareTestCase spare_cases[] = {
        {{1, 9}, true}, {{5, 5}, true}, {{3, 4}, false}, {{0, 10}, true}, {{10, 0}, false}, // strike, not spare
};

INSTANTIATE_TEST_SUITE_P(SpareCases, SpareTests, ::testing::ValuesIn(spare_cases));
