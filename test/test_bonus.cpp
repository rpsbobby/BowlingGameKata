//
// Created by robert on 11/22/25.
//

#include <array>

#include "bonus.hpp"
#include "gtest/gtest.h"

TEST(BonusTest, should_create_default_bonus) {
    Bonus b;
    EXPECT_EQ(b.first, -1);
    EXPECT_EQ(b.second, -1);
    EXPECT_EQ(b.type, BonusType::None);
}

TEST(BonusTest, should_create_valid_strike) {
    Bonus b(BonusType::Strike, 10, 10);
    EXPECT_EQ(b.first, 10);
    EXPECT_EQ(b.second, 10);
}

TEST(BonusTest, should_create_valid_spare) {
    Bonus b(BonusType::Spare, 10);
    EXPECT_EQ(b.first, 10);
    EXPECT_EQ(b.second, -1);
}

TEST(BonusTest, shoudl_throw_on_invalud_strike) { EXPECT_THROW(Bonus b(BonusType::Strike, 10), std::invalid_argument); }
