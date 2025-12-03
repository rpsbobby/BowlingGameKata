//
// Created by robert on 11/23/25.
//

#include "bonus.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "tests_utils.hpp"

struct AddBonusTestCase {
    BonusType type;
    int r1;
    int r2;
    bool should_throw;
    FrameFactoryHelper option;
    bool expected = false;
};

class CounterAddBonusSuite : public testing::TestWithParam<AddBonusTestCase> {};

TEST_P(CounterAddBonusSuite, should_validate_bonus_addition) {
    const auto &[type, r1, r2, should_throw, option, expected] = GetParam();
    FrameCounter counter;
    const Bonus bonus(type, r1, r2);
    for (const auto &frame: make_frames(option)) {
        counter.add_frame(frame);
    }
    if (should_throw) {
        EXPECT_THROW(counter.add_bonus(bonus), std::invalid_argument);
    } else {
        bool actual = false;
        EXPECT_NO_THROW(actual = counter.add_bonus(bonus));
        ASSERT_EQ(actual, expected);
    }
}

static const AddBonusTestCase bonus_test_cases[] = {
        {BonusType::None, -1, -1, true, FrameFactoryHelper::COMPLETE}, // complete - no bonus allowed
        {BonusType::None, -1, -1, true, FrameFactoryHelper::INCOMPLETE}, // incomplete - bo bonus
        {BonusType::None, -1, -1, true, FrameFactoryHelper::STRIKE},
        {BonusType::None, -1, -1, true, FrameFactoryHelper::SPARE},

        {BonusType::Spare, 10, -1, true, FrameFactoryHelper::INCOMPLETE},
        {BonusType::Spare, 10, -1, true, FrameFactoryHelper::INCOMPLETE},
        {BonusType::Spare, 10, -1, true, FrameFactoryHelper::COMPLETE},
        {BonusType::Spare, 10, -1, true, FrameFactoryHelper::COMPLETE},
        {BonusType::Spare, 10, -1, false, FrameFactoryHelper::SPARE, true},
        {BonusType::Spare, 10, -1, true, FrameFactoryHelper::STRIKE},
        //
        {BonusType::Strike, 10, 1, false, FrameFactoryHelper::STRIKE, true},
        {BonusType::Strike, 10, 1, true, FrameFactoryHelper::SPARE},
        {BonusType::Strike, 10, 1, true, FrameFactoryHelper::INCOMPLETE},
        {BonusType::Strike, 10, 1, true, FrameFactoryHelper::COMPLETE},

};

INSTANTIATE_TEST_SUITE_P(BonusValidationCases, CounterAddBonusSuite, ::testing::ValuesIn(bonus_test_cases));
