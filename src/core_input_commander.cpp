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

// -----------------------------------------------------------------------------
void CameraUpCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_up * camera.m_speed;
    });
}

void CameraDownCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_up * camera.m_speed;
    });
}

void CameraLeftCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_right * camera.m_speed;
    });
}

void CameraRightCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_right * camera.m_speed;
    });
}

void CameraForwardCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_front * camera.m_speed;
    });
}

void CameraBackwardCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_front * camera.m_speed;
    });
}

void CameraZoomInCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_zoom -= camera.m_speed;
        if (camera.m_zoom < 1.0f) {camera.m_zoom = 1.0f;}
    });
}

void CameraZoomOutCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_zoom += camera.m_speed;
        if (camera.m_zoom > 45.0f) {camera.m_zoom = 45.0f;}
    });
}