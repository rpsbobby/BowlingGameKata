//
// Created by robert on 11/22/25.
//

#include "frame_counter.hpp"

#include <stdexcept>

FrameCounter::FrameCounter():_frames() {
}

void FrameCounter::add_frame(Frame frame) {
    if (_frames.size()< 10)
        _frames.push_back(std::move(frame));
    else
        throw std::out_of_range("Too many frames, limit is 10");
}

size_t FrameCounter::get_frame_count() const {
    return _frames.size();
}

bool FrameCounter::is_complete() const {
    if (!with_bonus()) {
        return _frames.size() == 10;
    }
    return is_bonus_valid();
}

bool FrameCounter::add_bonus(Bonus bonus) {
    if (!with_bonus()) {
        throw std::invalid_argument("No bonus available for this game");
    }
    if (_frames.back().is_spare() && bonus.type != BonusType::Spare) {
        throw std::invalid_argument("Wrong type of bonus - spare bonus expected");
    }
    if (_frames.back().is_strike() && bonus.type != BonusType::Strike) {
        throw std::invalid_argument("Wrong type of bonus - strike bonus expected ");
    }
    _bonus.emplace(bonus);
    return _bonus.has_value();
}

int FrameCounter::get_score() const {
    if (!is_complete())
        throw std::logic_error("Cannot compute score: game is not complete");
    int score = 0;
    for (const auto &f: _frames) {
        score += f.first_roll();
        score += f.second_roll();
    }
    if (_bonus.has_value()) {
        if (_bonus.value().type == BonusType::Spare) {
            score += _bonus.value().first;
        } else if (_bonus.value().type == BonusType::Strike) {
            score += _bonus.value().first;
            score += _bonus.value().second;
        }
    }

    return  score;
}

bool FrameCounter::with_bonus() const {
    return _frames.size() == 10 && _frames.back().total() == 10;
}

bool FrameCounter::is_bonus_valid() const {
    bool frames_valid = with_bonus();
    if (!frames_valid || !_bonus.has_value())
        return false;
    if (_frames.back().is_strike())
        return _bonus.value().first != invalid && _bonus.value().second != invalid;

    return _bonus.value().first != invalid && _bonus.value().second == invalid;
}
