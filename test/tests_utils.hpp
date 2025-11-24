//
// Created by robert on 11/23/25.
//

#ifndef BOWLINGGAMEKATA_TESTS_UTILS_HPP
#define BOWLINGGAMEKATA_TESTS_UTILS_HPP

#include <vector>
#include "Frame.hpp"
// ---------------------------------------------
// HELPER FUNCTIONS
// ---------------------------------------------
enum class FrameFactoryHelper {
    STRIKE = 1,
    SPARE,
    COMPLETE,
    INCOMPLETE,
    GUTTER,
    ONES
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

inline std::vector<Frame> make_gutter() {
    return std::vector<Frame>(10, Frame{0, 0});
}

inline std::vector<Frame> make_ones() {
    return std::vector<Frame>(10, Frame{1, 1});
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
        case FrameFactoryHelper::GUTTER:
            return make_gutter();
        case FrameFactoryHelper::ONES:
            return make_ones();
        default:
            return {};
    }
}

// ---------------------------------------------
// BONUS

enum class BonusFactoryHelper {
    STRIKE_5 = 1,
    SPARE_5,
    STRIKE_10,
    SPARE_10,
    NONE,
};

inline Bonus make_bonus_strike_5() {
    return {BonusType::Strike, 5, 5};
}

inline Bonus make_bonus_spare_5() {
    return {BonusType::Spare, 5};
}

inline Bonus make_bonus_strike_10() {
    return {BonusType::Strike, 10, 10};
}

inline Bonus make_bonus_spare_10() {
    return {BonusType::Spare, 10};
}

inline Bonus make_bonus_none() {
    return {BonusType::None, -1, -1};
}

inline Bonus make_bonus(const BonusFactoryHelper option) {
    switch (option) {
        case BonusFactoryHelper::SPARE_5:
            return make_bonus_spare_5();
            break;
        case BonusFactoryHelper::STRIKE_5:
            return make_bonus_strike_5();
            break;
        case BonusFactoryHelper::SPARE_10:
            return make_bonus_spare_10();
            break;
        case BonusFactoryHelper::STRIKE_10:
            return make_bonus_strike_10();
            break;
        case BonusFactoryHelper::NONE:
            return make_bonus_none();
        default:
            return {};
    }
}


// ---------------------------------------------


#endif //BOWLINGGAMEKATA_TESTS_UTILS_HPP
