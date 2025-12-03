//
// Created by robert on 12/2/25.
//

#ifndef BOWLINGGAMEKATA_RANDOM_FUZZ_UTILS_HPP
#define BOWLINGGAMEKATA_RANDOM_FUZZ_UTILS_HPP

#include <random>
#include "Frame.hpp"
#include "bonus.hpp"

inline int rand_int(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

inline Frame random_valid_frame() {
    const int first = rand_int(0, 10);
    if (first == 10)
        return Frame{10, 0};

    const int second = rand_int(0, 10 - first);
    return Frame{first, second};
}

inline Bonus random_valid_bonus_for(const Frame &f) {
    if (f.is_spare()) {
        const int r = rand_int(0, 10);
        return {BonusType::Spare, r};
    }

    if (f.is_strike()) {
        const int r1 = rand_int(0, 10);
        const int r2 = rand_int(0, 10);
        return {BonusType::Strike, r1, r2};
    }

    return {}; // no bonus needed
}

#endif // BOWLINGGAMEKATA_RANDOM_FUZZ_UTILS_HPP
