//
// Created by robert on 12/2/25.
//

#include "Frame.hpp"
#include "bonus.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "random_fuzz_utils.hpp"

TEST(Fuzzing, valid_random_games_should_not_throw) {
    constexpr int ITER = 2000;

    for (int i = 0; i < ITER; ++i) {
        FrameCounter counter;

        // 9 random frames
        for (int f = 0; f < 9; ++f)
            counter.add_frame(random_valid_frame());

        // last frame
        Frame last = random_valid_frame();
        counter.add_frame(last);

        // add bonus if needed
        if (last.is_spare() || last.is_strike()) {
            Bonus b = random_valid_bonus_for(last);
            counter.add_bonus(b);
        }

        EXPECT_NO_THROW(counter.get_score());
        int score = counter.get_score();

        EXPECT_GE(score, 0);
        EXPECT_LE(score, 300);
    }
}
