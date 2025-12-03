//
// Created by robert on 11/24/25.
#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "tests_utils.hpp"

TEST(ScoreFreestanding, should_throw_when_score_called_but_frames_are_missing) {
    FrameCounter counter;
    for (const auto &f: make_frames(FrameFactoryHelper::INCOMPLETE))
        counter.add_frame(f);
    EXPECT_THROW(counter.get_score(), std::logic_error);
}

TEST(ScoreFreestanding, should_throw_when_score_called_but_spare_bonus_missing) {
    FrameCounter counter;
    for (const auto &f: make_frames(FrameFactoryHelper::SPARE))
        counter.add_frame(f);
    EXPECT_THROW(counter.get_score(), std::logic_error);
}

TEST(ScoreFreestanding, should_throw_when_score_called_but_strike_bonus_missing) {
    FrameCounter counter;
    for (const auto &f: make_frames(FrameFactoryHelper::STRIKE))
        counter.add_frame(f);
    EXPECT_THROW(counter.get_score(), std::logic_error);
}

TEST(ScoreFreestanding, should_not_throw_when_score_called_and_game_is_complete) {
    FrameCounter counter;

    // 10 strikes → needs 2 bonuses
    for (const auto &f: make_frames(FrameFactoryHelper::STRIKE))
        counter.add_frame(f);

    counter.add_bonus(Bonus{BonusType::Strike, 10, 10});

    EXPECT_NO_THROW(counter.get_score());
}
