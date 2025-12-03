//
// Created by robert on 11/22/25.
//

#include "frame_counter.hpp"

#include <stdexcept>

#include "errors.hpp"

using namespace bowling;

FrameCounter::FrameCounter() : _frames() {}

void FrameCounter::add_frame(Frame frame) {
    if (_frames.size() < max_frames)
        _frames.push_back(std::move(frame));
    else
        throw TooManyFramesError("Too many frames, limit is 10");
}

size_t FrameCounter::get_frame_count() const { return _frames.size(); }

bool FrameCounter::is_complete() const noexcept {
    if (!with_bonus()) {
        return _frames.size() == max_frames;
    }
    return is_bonus_valid();
}

bool FrameCounter::add_bonus(Bonus bonus) {
    if (!with_bonus()) {
        throw InvalidBonusError("No bonus available for this game");
    }
    if (_frames.back().is_spare() && bonus.type != BonusType::Spare) {
        throw InvalidBonusError("Wrong type of bonus - spare bonus expected");
    }
    if (_frames.back().is_strike() && bonus.type != BonusType::Strike) {
        throw InvalidBonusError("Wrong type of bonus - strike bonus expected ");
    }
    _bonus.emplace(bonus);
    return _bonus.has_value();
}

int FrameCounter::get_score() const {
    if (!is_complete())
        throw IncompleteGameError("Cannot compute score: game is not complete");
    const auto rolls = get_rolls();
    int score = 0;
    size_t i = 0;
    // Score 10 frames
    for (const auto &f: _frames) {
        score += score_frame(f, rolls, i);
    }
    return score;
}

bool FrameCounter::with_bonus() const { return _frames.size() == max_frames && _frames.back().is_max(); }

bool FrameCounter::is_bonus_valid() const {
    if (bool frames_valid = with_bonus(); !frames_valid || !_bonus.has_value())
        return false;
    if (_frames.back().is_strike())
        return _bonus.value().first != invalid && _bonus.value().second != invalid;

    return _bonus.value().first != invalid && _bonus.value().second == invalid;
}

std::vector<int> FrameCounter::get_rolls() const {
    std::vector<int> rolls;
    for (auto &f: _frames) {
        rolls.push_back(f.first_roll());
        if (!f.is_strike())
            rolls.push_back(f.second_roll());
    }
    if (_bonus) {
        rolls.push_back(_bonus->first);
        if (_bonus->type == BonusType::Strike)
            rolls.push_back(_bonus->second);
    }
    return rolls;
}

int FrameCounter::score_frame(const Frame &f, const std::vector<int> &rolls, size_t &index) const {
    int score = 0;
    if (f.is_strike()) {
        score += Frame::MAX_SCORE + rolls[index + 1] + rolls[index + 2];
        index += 1;
        return score;
    }
    if (f.is_spare()) {
        score += Frame::MAX_SCORE + rolls[index + 2];
        index += 2;
        return score;
    }
    score += rolls[index] + rolls[index + 1];
    index += 2;
    return score;
}
