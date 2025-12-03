//
// Created by robert on 11/23/25.
//

#include "bonus.hpp"
#include "gtest/gtest.h"

struct InvalidBonusCase {
    BonusType type;
    int first;
    int second;
};

class InvalidBonusTests : public testing::TestWithParam<InvalidBonusCase> {};

TEST_P(InvalidBonusTests, should_throw_on_invalid_bonus) {
    auto const &[type, first, second] = GetParam();
    EXPECT_THROW(Bonus(type, first, second), std::invalid_argument);
}

static constexpr InvalidBonusCase invalid_bonus_cases[] = {
        {BonusType::Spare, 11, -1}, // too big
        {BonusType::Spare, -1, -1}, // invalid first roll
        {BonusType::Spare, -1, 1}, // invalid first, and second
        {BonusType::Spare, 5, 1}, // spare can't have second roll

        {BonusType::None, 1, 1}, // None cannot have rolls
        {BonusType::None, 1, 0},
        {BonusType::None, 11, -1},
        {BonusType::None, 11, 0},
        {BonusType::None, 5, 1},
        //
        {BonusType::Strike, -1, 2}, // invalid numbers
        {BonusType::Strike, 11, 0}, // first invalid
        {BonusType::Strike, -1, 5}, // first invalid
        {BonusType::Strike, 3, 11}, // second invalid
        {BonusType::Strike, 3, -12}, // second invalid
};

INSTANTIATE_TEST_SUITE_P(InvalidBonusCases, InvalidBonusTests, ::testing::ValuesIn(invalid_bonus_cases));
