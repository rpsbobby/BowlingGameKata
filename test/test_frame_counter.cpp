//
// Created by robert on 11/22/25.
//
#include "bonus.hpp"
#include "Frame.hpp"
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
    EXPECT_THROW(counter.add_frame(f), std::out_of_range);
}
