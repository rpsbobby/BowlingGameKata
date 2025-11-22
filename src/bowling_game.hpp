//
// Created by robert on 11/22/25.
//

#ifndef BOWLINGGAMEKATA_GAME_HPP
#define BOWLINGGAMEKATA_GAME_HPP
#include "Frame.hpp"

class BowlingGame {

public:
    BowlingGame() = default;
    ~BowlingGame() = default;


    bool add_frame(Frame&& frame);
};


#endif //BOWLINGGAMEKATA_GAME_HPP