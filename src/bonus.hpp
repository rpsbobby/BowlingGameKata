//
// Created by robert on 11/22/25.
//

#ifndef BOWLINGGAMEKATA_BONUS_HPP
#define BOWLINGGAMEKATA_BONUS_HPP

#include "errors.hpp"
using namespace bowling;

enum class BonusType { None, Spare, Strike };

struct Bonus {
    const BonusType type;
    const int first;
    const int second;

    Bonus();

    Bonus(BonusType t, int r1, int r2 = invalid);
    ;

private:
    static constexpr int invalid = -1;

    void validate() const;
};

#endif // BOWLINGGAMEKATA_BONUS_HPP
