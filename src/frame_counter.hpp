//
// Created by robert on 11/22/25.
//

#ifndef BOWLINGGAMEKATA_FRAME_COUNTER_HPP
#define BOWLINGGAMEKATA_FRAME_COUNTER_HPP
#include <type_traits>
#include <vector>

#include "bonus.hpp"
#include "Frame.hpp"


class FrameCounter {
public:
    explicit FrameCounter();
    void add_frame(Frame frame);
    size_t get_frame_count() const;
    bool is_complete() const;
    bool add_bonus(Bonus bonus);

private:
    bool with_bonus() const;
    bool is_bonus_valid() const;

    std::vector<Frame> _frames;
    Bonus _bonus;
    static constexpr int invalid = -1;
};


#endif //BOWLINGGAMEKATA_FRAME_COUNTER_HPP
