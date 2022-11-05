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
        camera.m_zoom -= camera.m_sensitivity;
        if (camera.m_zoom < 1.0f) {camera.m_zoom = 1.0f;}
    });
}

void CameraZoomOutCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_zoom += camera.m_sensitivity;
        if (camera.m_zoom > 45.0f) {camera.m_zoom = 45.0f;}
    });
}

void CameraPitchUpCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_pitch += camera.m_sensitivity;
        if (camera.m_pitch > 89.0f) {camera.m_pitch = 89.0f;}
        // update vectors
        glm::vec3 front;
        front.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        front.y = sin(glm::radians(camera.m_pitch));
        front.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        camera.m_front = glm::normalize(front);
        camera.m_right = glm::normalize(glm::cross(camera.m_front, camera.m_worldUp));
        camera.m_up = glm::normalize(glm::cross(camera.m_right, camera.m_front));
    });
}

void CameraPitchDownCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_pitch -= camera.m_sensitivity;
        if (camera.m_pitch < -89.0f) {camera.m_pitch = -89.0f;}
        // update vectors
        glm::vec3 front;
        front.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        front.y = sin(glm::radians(camera.m_pitch));
        front.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        camera.m_front = glm::normalize(front);
        camera.m_right = glm::normalize(glm::cross(camera.m_front, camera.m_worldUp));
        camera.m_up = glm::normalize(glm::cross(camera.m_right, camera.m_front));
    });
}

void CameraYawLeftCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_yaw -= camera.m_sensitivity;
        // update vectors
        glm::vec3 front;
        front.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        front.y = sin(glm::radians(camera.m_pitch));
        front.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        camera.m_front = glm::normalize(front);
        camera.m_right = glm::normalize(glm::cross(camera.m_front, camera.m_worldUp));
        camera.m_up = glm::normalize(glm::cross(camera.m_right, camera.m_front));
    });
}

void CameraYawRightCommand::execute(entt::registry& registry) const {
    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_yaw += camera.m_sensitivity;
        // update vectors
        glm::vec3 front;
        front.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        front.y = sin(glm::radians(camera.m_pitch));
        front.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        camera.m_front = glm::normalize(front);
        camera.m_right = glm::normalize(glm::cross(camera.m_front, camera.m_worldUp));
        camera.m_up = glm::normalize(glm::cross(camera.m_right, camera.m_front));
    });
}