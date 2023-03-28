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
    dispatcher.enqueue<LeftCommand>();
}

void DownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<DownCommand>();
}

void RightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<RightCommand>();
}

void UpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<UpCommand>();
}

void SelectedLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<SelectedLeftCommand>();
}

void SelectedDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<SelectedDownCommand>();
}

void SelectedRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<SelectedRightCommand>();
}

void SelectedUpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<SelectedUpCommand>();
}


void ToggleSelectModeCommand::execute(entt::dispatcher& dispatcher) const {    
    dispatcher.enqueue<ToggleSelectModeCommand>();
    dispatcher.enqueue<ToggleSelectModeAudioEvent>();
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
    dispatcher.enqueue<CameraUpCommand>();
}

void CameraDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraDownCommand>();
}

void CameraLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraLeftCommand>();
}

void CameraRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraRightCommand>();
}

void CameraForwardCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraForwardCommand>();
}

void CameraBackwardCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraBackwardCommand>();
}

void CameraZoomInCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraZoomInCommand>();
}

void CameraZoomOutCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraZoomOutCommand>();
}

void CameraPitchUpCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraPitchUpCommand>();
}

void CameraPitchDownCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraPitchDownCommand>();
}

void CameraYawLeftCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraYawLeftCommand>();
}

void CameraYawRightCommand::execute(entt::dispatcher& dispatcher) const {
    dispatcher.enqueue<CameraYawRightCommand>();
}