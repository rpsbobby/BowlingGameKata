//
// Created by robert on 11/23/25.
//

#include "frame_counter.hpp"
#include "tests_utils.hpp"
#include "gtest/gtest.h"

struct ScoreTestCases {
    FrameFactoryHelper option;
    const BonusFactoryHelper bonus;
    int expected;
};

class ScoreTests : public testing::TestWithParam<ScoreTestCases> {
};

TEST_P(ScoreTests, should_validate_final_score) {
    auto const &[option, bonus_option, expected] = GetParam();
    FrameCounter counter;
    for (auto const &f: make_frames(option))
        counter.add_frame(f);
    if (bonus_option != BonusFactoryHelper::NONE)
        counter.add_bonus(make_bonus(bonus_option));

    int actual = counter.get_score();
    ASSERT_EQ(expected, actual);
}

static constexpr ScoreTestCases score_cases[] = {
    {FrameFactoryHelper::GUTTER, BonusFactoryHelper::NONE, 0,},
    {FrameFactoryHelper::ONES, BonusFactoryHelper::NONE, 20,},
    {FrameFactoryHelper::COMPLETE, BonusFactoryHelper::NONE, 90,},
    {FrameFactoryHelper::SPARE, BonusFactoryHelper::SPARE_0, 100},
    {FrameFactoryHelper::SPARE, BonusFactoryHelper::SPARE_5, 105},
    {FrameFactoryHelper::SPARE, BonusFactoryHelper::SPARE_10, 110},
    {FrameFactoryHelper::ZEROS_AND_LAST_STRIKE, BonusFactoryHelper::STRIKE_10, 30}
};

INSTANTIATE_TEST_SUITE_P(
    ScoreTestCases,
    ScoreTests,
    ::testing::ValuesIn(score_cases)
);
