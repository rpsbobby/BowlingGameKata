#include "bonus.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "tests_utils.hpp"
enum class FrameFactoryHelper;
//
// Created by robert on 11/23/25.
//
struct CompletenessBonusCase {
    FrameFactoryHelper option;
    Bonus bonus;
    bool expected;
};

class CompletenessBonusTests : public testing::TestWithParam<CompletenessBonusCase> {};

TEST_P(CompletenessBonusTests, should_complete_after_valid_bonus) {
    const auto &[option, bonus, expected] = GetParam();

    FrameCounter counter;

    for (const auto &f: make_frames(option))
        counter.add_frame(f);

    EXPECT_NO_THROW(counter.add_bonus(bonus));
    EXPECT_EQ(counter.is_complete(), expected);
}

static const CompletenessBonusCase completeness_bonus_cases[] = {
        {FrameFactoryHelper::SPARE, Bonus(BonusType::Spare, 8), true},
        {FrameFactoryHelper::STRIKE, Bonus(BonusType::Strike, 8, 8), true},
};

INSTANTIATE_TEST_SUITE_P(CompletenessBonusCases, CompletenessBonusTests, ::testing::ValuesIn(completeness_bonus_cases));
