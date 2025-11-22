//
// Created by robert on 11/22/25.
//
#include "bonus.hpp"
#include "Frame.hpp"
#include "frame_counter.hpp"
#include "gtest/gtest.h"

// ---------------------------------------------
// HELPER FUNCTIONS
// ---------------------------------------------
enum class FrameFactoryHelper {
    STRIKE = 1,
    SPARE,
    COMPLETE,
    INCOMPLETE
};

inline std::vector<Frame> make_strike() {
    return std::vector<Frame>(10, Frame{10, 0});
}

inline std::vector<Frame> make_complete() {
    return std::vector<Frame>(10, Frame{5, 4});
}

inline std::vector<Frame> make_incomplete() {
    return std::vector<Frame>(9, Frame{5, 4});
}

inline std::vector<Frame> make_spare() {
    return std::vector<Frame>(10, Frame{5, 5});
}

inline std::vector<Frame> make_frames(FrameFactoryHelper option) {
    switch (option) {
        case FrameFactoryHelper::STRIKE:
            return make_strike();
        case FrameFactoryHelper::SPARE:
            return make_spare();
        case FrameFactoryHelper::COMPLETE:
            return make_complete();
        case FrameFactoryHelper::INCOMPLETE:
            return make_incomplete();
        default:
            return {};
    }
}

// ---------------------------------------------

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

// ---------------------------------------------
// COMPLETENESS CASES
// ---------------------------------------------

struct CompleteTestCase {
    int number_of_frames;
    Frame last_frame;
    bool expected;
};

class CompletenessTests : public ::testing::TestWithParam<CompleteTestCase> {
};

TEST_P(CompletenessTests, should_throw_on_invalid_args) {
    const auto &[number_of_frames, last_frame, expected] = GetParam();
    FrameCounter counter;
    const Frame f{5, 4};
    for (int i = 0; i < number_of_frames; ++i)
        counter.add_frame(f);
    counter.add_frame(last_frame);
    const auto actual = counter.is_complete();
    EXPECT_EQ(actual, expected);
}

static const CompleteTestCase completeness_cases[] = {
    {5, Frame{5, 4}, false},
    {9, Frame{5, 4}, true},
    {9, Frame{10, 0}, false},
    {9, Frame{5, 5}, false},
};

INSTANTIATE_TEST_SUITE_P(
    CompleteTestCase,
    CompletenessTests,
    ::testing::ValuesIn(completeness_cases)
);
// ---------------------------------------------
// COMPLETENESS CASES - END
// ---------------------------------------------

// ---------------------------------------------
// BONUS ADDITION
// ---------------------------------------------

struct BonusTestCase {
    Bonus type;
    bool should_throw;
    FrameFactoryHelper option;
};


class BonusTests : public ::testing::TestWithParam<BonusTestCase> {
};


TEST_P(BonusTests, should_validate_bonus_constructor) {
    const auto &[bonus, should_throw, option] = GetParam();
    FrameCounter counter;
    for (const auto &frame : make_frames(option)) {
        counter.add_frame(frame);
    }
    if (should_throw) {
        EXPECT_THROW(counter.add_bonus(bonus), std::invalid_argument);
    } else {
        EXPECT_NO_THROW(counter.add_bonus(bonus));
    }
}

static const BonusTestCase bonus_test_cases[] = {
    {Bonus(), true, FrameFactoryHelper::COMPLETE},
{Bonus(), true, FrameFactoryHelper::INCOMPLETE},
};

INSTANTIATE_TEST_SUITE_P(
    BonusValidationCases,
    BonusTests,
    ::testing::ValuesIn(bonus_test_cases)
);
