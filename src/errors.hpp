//
// Created by robert on 12/2/25.
//

#ifndef BOWLINGGAMEKATA_ERRORS_HPP
#define BOWLINGGAMEKATA_ERRORS_HPP

#include <stdexcept>
#include <string>

namespace bowling {

    struct InvalidRollError : public std::invalid_argument {
        explicit InvalidRollError(const std::string &msg) : std::invalid_argument(msg) {}
    };

    struct IncompleteGameError : public std::logic_error {
        explicit IncompleteGameError(const std::string &msg) : std::logic_error(msg) {}
    };

    struct TooManyFramesError : public std::logic_error {
        explicit TooManyFramesError(const std::string &msg) : std::logic_error(msg) {}
    };

    struct InvalidBonusError : public std::invalid_argument {
        explicit InvalidBonusError(const std::string &msg) : std::invalid_argument(msg) {}
    };

} // namespace bowling

#endif // BOWLINGGAMEKATA_ERRORS_HPP
