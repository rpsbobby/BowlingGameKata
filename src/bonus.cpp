//
// Created by robert on 11/22/25.
//

#include "bonus.hpp"

Bonus::Bonus() : type(BonusType::None), first(invalid), second(invalid) {}

Bonus::Bonus(BonusType t, int r1, int r2) : type(t), first(r1), second(r2) { validate(); }

void Bonus::validate() const {
    switch (type) {
        case BonusType::Strike:
            if (first < 0 || first > 10 || second < 0 || second > 10) {
                throw InvalidBonusError("invalid strike bonus!");
            }
            break;
        case BonusType::Spare:
            if (first < 0 || first > 10 || second != invalid) {
                throw InvalidBonusError("invalid spare bonus!");
            }
            break;
        case BonusType::None:
            if (first != invalid || second != invalid) {
                throw InvalidBonusError("invalid default bonus!");
            }
            break;
        default:
            throw InvalidBonusError("unsupported bonus type");
            break;
    }
}
