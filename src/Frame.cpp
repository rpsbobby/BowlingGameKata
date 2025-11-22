//
// Created by robert on 11/20/25.
//

#include "Frame.hpp"

#include <stdexcept>

Frame::Frame(int first_roll, int second_roll) : _first_roll(first_roll), _second_roll(second_roll) {
    validate_input();
}

int Frame::total() const {
    return _first_roll + _second_roll;
}

bool Frame::is_strike() const {
    return _first_roll == 10;
}

bool Frame::is_spare() const {
    return total() == 10 && _first_roll != 10;
}

void Frame::validate_input() {
    if (_first_roll > 10 || _first_roll < 0 || _second_roll > 10 || _second_roll < 0)
        throw std::invalid_argument("Roll must be between 0 and 10");
    if (_first_roll == 10 && _second_roll != 0)
        throw std::invalid_argument("Strike can only have only one roll");
    if (total() > 10)
        throw std::invalid_argument("Total must be between 0 and 10");
}
