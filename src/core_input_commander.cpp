// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_commander.cpp
//  uses COMMANDER design pattern
//  contains code to execute for all input commands (via keyboard, mouse, etc)
// -----------------------------------------------------------------------------

#include "core_input_commander.h"

// -----------------------------------------------------------------------------
void LeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<LeftCommand>();
}

void DownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<DownCommand>();
}

void RightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<RightCommand>();
}

void UpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<UpCommand>();
}

void SelectedLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<SelectedLeftCommand>();
}

void SelectedDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<SelectedDownCommand>();
}

void SelectedRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<SelectedRightCommand>();
}

void SelectedUpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<SelectedUpCommand>();
}


void ToggleSelectModeCommand::execute(entt::dispatcher& dispatcher) const {    
    dispatcher.trigger<ToggleSelectModeCommand>();
}

// -----------------------------------------------------------------------------
void NorthCommand::execute(entt::dispatcher& dispatcher) const {
}

void WestCommand::execute(entt::dispatcher& dispatcher) const {
}

void SouthCommand::execute(entt::dispatcher& dispatcher) const {
}

void EastCommand::execute(entt::dispatcher& dispatcher) const {
}

void NortheastCommand::execute(entt::dispatcher& dispatcher) const {
}

void NorthwestCommand::execute(entt::dispatcher& dispatcher) const {
}

void SouthwestCommand::execute(entt::dispatcher& dispatcher) const {
}

void SoutheastCommand::execute(entt::dispatcher& dispatcher) const {
}

// -----------------------------------------------------------------------------
void CameraUpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraUpCommand>();
}

void CameraDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraDownCommand>();
}

void CameraLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraLeftCommand>();
}

void CameraRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraRightCommand>();
}

void CameraForwardCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraForwardCommand>();
}

void CameraBackwardCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraBackwardCommand>();
}

void CameraZoomInCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraZoomInCommand>();
}

void CameraZoomOutCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraZoomOutCommand>();
}

void CameraPitchUpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraPitchUpCommand>();
}

void CameraPitchDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraPitchDownCommand>();
}

void CameraYawLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraYawLeftCommand>();
}

void CameraYawRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.trigger<CameraYawRightCommand>();
}