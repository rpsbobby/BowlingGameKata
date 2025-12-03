//
// Created by robert on 11/23/25.
//

#include "frame_counter.hpp"
#include "gtest/gtest.h"
#include "tests_utils.hpp"

struct CompletenessCase {
    FrameFactoryHelper option;
    bool expected;
};

class CompletenessTests : public testing::TestWithParam<CompletenessCase> {};

TEST_P(CompletenessTests, should_report_correct_basic_completeness) {
    const auto &[option, expected] = GetParam();

    FrameCounter counter;

    for (const auto &f: make_frames(option)) {
        counter.add_frame(f);
    }

    EXPECT_EQ(counter.is_complete(), expected);
}

static const CompletenessCase completeness_cases[] = {
        {FrameFactoryHelper::INCOMPLETE, false},
        {FrameFactoryHelper::COMPLETE, true},
        {FrameFactoryHelper::SPARE, false}, // spare needs 1 bonus
        {FrameFactoryHelper::STRIKE, false}, // strike needs 2 bonus rolls
};

INSTANTIATE_TEST_SUITE_P(CompletenessCases, CompletenessTests, ::testing::ValuesIn(completeness_cases));
