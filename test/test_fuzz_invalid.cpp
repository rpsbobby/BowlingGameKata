//
// Created by robert on 12/2/25.
//
#include "bonus.hpp"
#include "errors.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "random_fuzz_utils.hpp"

using namespace bowling;

TEST(Fuzzing, random_input_should_only_throw_expected_errors) {
    constexpr int ITER = 3000;

    for (int i = 0; i < ITER; ++i) {
        FrameCounter counter;

        // --------------------------------------
        // 1) Random frame construction + adding
        // --------------------------------------
        for (int f = 0; f < 12; ++f) {
            // may attempt too many
            try {
                int a = rand_int(-3, 13);
                int b = rand_int(-3, 13);

                Frame frame(a, b); // may throw InvalidRollError
                counter.add_frame(frame); // may throw TooManyFramesError
            } catch (const InvalidRollError &) {
                // valid expected error
            } catch (const TooManyFramesError &) {
                // valid expected error
            } catch (const std::invalid_argument &) {
                // Frame validation uses std::invalid_argument in your model
            } catch (...) {
                FAIL() << "Unexpected exception type while constructing/adding frame";
            }
        }

        // --------------------------------------
        // 2) Random bonus attempt
        // --------------------------------------
        try {
            BonusType t = (rand_int(0, 1) == 0) ? BonusType::Strike : BonusType::Spare;

            int r1 = rand_int(-3, 13);
            int r2 = rand_int(-3, 13);

            Bonus b(t, r1, r2); // may throw InvalidBonusError
            counter.add_bonus(b); // may throw InvalidBonusError
        } catch (const InvalidBonusError &) {
            // expected: spare/strike mismatch or invalid values
        } catch (const std::invalid_argument &) {
            // also expected depending on constructor validation
        } catch (...) {
            FAIL() << "Unexpected exception type while constructing/adding bonus";
        }

        // --------------------------------------
        // 3) Scoring – may throw incomplete game
        // --------------------------------------
        try {
            int score = counter.get_score();

            // sanity checks only apply if no exception thrown
            EXPECT_GE(score, 0);
            EXPECT_LE(score, 300);
        } catch (const IncompleteGameError &) {
            // expected: random input usually leaves incomplete game
        } catch (...) {
            FAIL() << "Unexpected exception type during get_score()";
        }
    }
}
