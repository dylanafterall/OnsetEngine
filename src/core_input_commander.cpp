// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_commander.cpp
//  uses COMMANDER design pattern
//  contains code to execute for all input commands (via keyboard, mouse, etc)
// -----------------------------------------------------------------------------

#include "core_input_commander.hpp"

void LeftCommand::execute() const {
    std::cout << "Move left" << std::endl;
}

void DownCommand::execute() const {
    std::cout << "Move down" << std::endl;
}

void RightCommand::execute() const {
    std::cout << "Move right" << std::endl;
}

void UpCommand::execute() const {
    std::cout << "Move up" << std::endl;
}