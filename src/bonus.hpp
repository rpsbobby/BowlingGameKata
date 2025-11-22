//
// Created by robert on 11/22/25.
//

#ifndef BOWLINGGAMEKATA_BONUS_HPP
#define BOWLINGGAMEKATA_BONUS_HPP
#include <array>
#include <stdexcept>


enum class BonusType {
    None,
    Spare,
    Strike
};

struct Bonus {
    const BonusType type;
    const int first;
    const int second;

    Bonus() : type(BonusType::None), first(invalid), second(invalid) {
    }
    Bonus(BonusType t, int r1, int r2 = invalid)
        : type(t), first(r1), second(r2) {
        validate();
    };

private:
    static constexpr int invalid = -1;

    void validate() const {
        switch (type) {
            case BonusType::Strike:
                if (first < 0 || first > 10 || second < 0 || second > 10) {
                    throw std::invalid_argument("invalid strike bonus!");
                }
                break;
            case BonusType::Spare:
                if (first < 0 || first > 10 || second != invalid) {
                    throw std::invalid_argument("invalid spare bonus!");
                }
                break;
            default:
                throw std::invalid_argument("unsupported bonus type");
                break;
        }
    }
};

#endif //BOWLINGGAMEKATA_BONUS_HPP
