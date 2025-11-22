//
// Created by robert on 11/22/25.
//

#include "frame_counter.hpp"

#include <stdexcept>

FrameCounter::FrameCounter():_frames(),_bonus() {
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
}

bool FrameCounter::with_bonus() const {
    return _frames.size() == 10 && _frames.back().total() == 10;
}

bool FrameCounter::is_bonus_valid() const {
    bool frames_valid = with_bonus();
    if (_frames.back().is_strike())
        return _bonus.first != invalid && _bonus.second != invalid;

    return _bonus.first != invalid && _bonus.second == invalid;
}
