//
// Created by robert on 11/20/25.
//

#ifndef BOWLINGGAMEKATA_FRAME_HPP
#define BOWLINGGAMEKATA_FRAME_HPP

class Frame {
public:
    explicit Frame(int first_roll, int second_roll = 0);
    int total() const;
    bool is_strike() const;
    bool is_spare() const;

private:
    void validate_input();

    int _first_roll;
    int _second_roll;
};


#endif //BOWLINGGAMEKATA_FRAME_HPP
