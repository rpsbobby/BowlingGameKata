//
// Created by robert on 11/20/25.
//
#include <array>
#include <gtest/gtest.h>
#include "Frame.hpp"

// ---------------------------------------------
// INVALID CASES
// ---------------------------------------------

// ---------------------------------------------
// BASIC VALID TESTS
// ---------------------------------------------

TEST(Frame, should_create_valid_frame) {
    Frame frame{4, 3};
    ASSERT_EQ(frame.total(), 7);
}

TEST(Frame, should_create_valid_strike) {
    Frame frame{10};
    ASSERT_EQ(frame.total(), 10);
}

TEST(Frame, should_return_strike) {
    Frame frame{10};
    ASSERT_TRUE(frame.is_strike());
}

TEST(Frame, should_return_is_max_false_if_not_spare_or_strike) {
    Frame frame{4, 3};
    ASSERT_FALSE(frame.is_max());
}

TEST(Frame, should_return_is_max_true_if_spare) {
    Frame frame{4, 6};
    ASSERT_TRUE(frame.is_max());
}

TEST(Frame, should_return_is_max_true_if_strike) {
    Frame frame{10};
    ASSERT_TRUE(frame.is_max());
}
