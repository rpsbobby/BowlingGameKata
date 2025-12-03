//
// Created by robert on 11/22/25.
//
#include "Frame.hpp"
#include "bonus.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"

TEST(FrameCounterSuite, should_add_valid_frame) {
    // given
    FrameCounter counter;
    Frame f{5, 4};
    // when
    counter.add_frame(f);
    const auto temp = counter.get_frame_count();
    EXPECT_EQ(temp, 1);
}

TEST(FrameCounterSuite, shoudl_throw_above_10_frames) {
    // given
    FrameCounter counter;
    const Frame f{5, 4};
    for (int i = 0; i < 10; ++i)
        counter.add_frame(f);
    const auto s = counter.get_frame_count();
    EXPECT_EQ(s, 10);
    EXPECT_THROW(counter.add_frame(f), std::logic_error);
}

TEST(FrameCounterSuite, strike_bonus_second_zero_must_be_counted) {
    FrameCounter counter;

    // 9 empty frames
    for (int i = 0; i < 9; ++i)
        counter.add_frame(Frame{0, 0});

    // 10th frame is a strike
    counter.add_frame(Frame{10, 0});

    // Bonus: (10, 0)
    Bonus b(BonusType::Strike, 10, 0);
    counter.add_bonus(b);

    // Expected scoring:
    // frame 10 = 10 + 10 + 0 = 20
    EXPECT_EQ(counter.get_score(), 20);
}
