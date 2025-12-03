//
// Created by robert on 11/22/25.
//

#ifndef BOWLINGGAMEKATA_FRAME_COUNTER_HPP
#define BOWLINGGAMEKATA_FRAME_COUNTER_HPP
#include <optional>
#include <vector>

#include "Frame.hpp"
#include "bonus.hpp"

class FrameCounter {
public:
    explicit FrameCounter();
    void add_frame(Frame frame);
    size_t get_frame_count() const;
    bool is_complete() const noexcept;
    bool add_bonus(Bonus bonus);
    int get_score() const;

private:
    [[nodiscard]] bool with_bonus() const;
    [[nodiscard]] bool is_bonus_valid() const;
    [[nodiscard]] int calculate_base_score() const;
    [[nodiscard]] std::vector<int> get_rolls() const;
    int score_frame(const Frame &f, const std::vector<int> &rolls, size_t &index) const;

    std::vector<Frame> _frames;
    std::optional<Bonus> _bonus;
    static constexpr int invalid = -1;
    static constexpr int max_frames = 10;
};

#endif // BOWLINGGAMEKATA_FRAME_COUNTER_HPP
