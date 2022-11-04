// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_commander.cpp
//  uses COMMANDER design pattern
//  contains code to execute for all input commands (via keyboard, mouse, etc)
// -----------------------------------------------------------------------------

#include "core_input_commander.hpp"

// -----------------------------------------------------------------------------
void LeftCommand::execute(entt::registry& registry) const {
    std::cout << "Move left" << std::endl;
}

void DownCommand::execute(entt::registry& registry) const {
    std::cout << "Move down" << std::endl;
}

void RightCommand::execute(entt::registry& registry) const {
    std::cout << "Move right" << std::endl;
}

void UpCommand::execute(entt::registry& registry) const {
    std::cout << "Move up" << std::endl;
}

// -----------------------------------------------------------------------------
void NorthCommand::execute(entt::registry& registry) const {
    std::cout << "Moved North" << std::endl;
}

void WestCommand::execute(entt::registry& registry) const {
    std::cout << "Moved West" << std::endl;
}

void SouthCommand::execute(entt::registry& registry) const {
    std::cout << "Moved South" << std::endl;
}

void EastCommand::execute(entt::registry& registry) const {
    std::cout << "Moved East" << std::endl;
}

void NortheastCommand::execute(entt::registry& registry) const {
    std::cout << "Moved Northeast" << std::endl;
}

void NorthwestCommand::execute(entt::registry& registry) const {
    std::cout << "Moved Northwest" << std::endl;
}

void SouthwestCommand::execute(entt::registry& registry) const {
    std::cout << "Moved Southwest" << std::endl;
}

void SoutheastCommand::execute(entt::registry& registry) const {
    std::cout << "Moved Southeast" << std::endl;
}