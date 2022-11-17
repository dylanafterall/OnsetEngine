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
void LeftCommand::execute(entt::registry& registry) const {
    auto player = registry.view<
        PlayerComponent,
        BodyCircleComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(-500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void DownCommand::execute(entt::registry& registry) const {
    auto player = registry.view<
        PlayerComponent,
        BodyCircleComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(0.0f, -2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void RightCommand::execute(entt::registry& registry) const {
    auto player = registry.view<
        PlayerComponent,
        BodyCircleComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void UpCommand::execute(entt::registry& registry) const {
    auto player = registry.view<
        PlayerComponent,
        BodyCircleComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(0.0f, 2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

// -----------------------------------------------------------------------------
void NorthCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved north");
}

void WestCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved west");
}

void SouthCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved south");
}

void EastCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved east");
}

void NortheastCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved northeast");
}

void NorthwestCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved northwest");
}

void SouthwestCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved southwest");
}

void SoutheastCommand::execute(entt::registry& registry) const {
    ONSET_TRACE("moved southeast");
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