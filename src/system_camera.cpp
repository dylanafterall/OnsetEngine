// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.cpp
//  system to control camera movement
// -----------------------------------------------------------------------------

#include "system_camera.h"

void CameraSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void CameraSystem::update(const float timeStep) {
    // get the player position, in order to provide translate transform to camera
    glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f);
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        translate[0] = position.x;
        translate[1] = position.y;
    });

    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position[0] = translate[0];
        camera.m_position[1] = translate[1];
    });
}

void CameraSystem::translateCameraLeft() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_right * camera.m_speed;
    });
}

void CameraSystem::translateCameraRight() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_right * camera.m_speed;
    });
}

void CameraSystem::translateCameraUp() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_up * camera.m_speed;
    });
}

void CameraSystem::translateCameraDown() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_up * camera.m_speed;
    });
}

void CameraSystem::translateCameraForward() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position += camera.m_front * camera.m_speed;
    });
}

void CameraSystem::translateCameraBackward() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position -= camera.m_front * camera.m_speed;
    });
}


void CameraSystem::zoomCameraIn() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_zoom -= camera.m_sensitivity;
        if (camera.m_zoom < 1.0f) {camera.m_zoom = 1.0f;}
    });
}

void CameraSystem::zoomCameraOut() {
    auto cameras = (*m_registry).view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_zoom += camera.m_sensitivity;
        if (camera.m_zoom > 45.0f) {camera.m_zoom = 45.0f;}
    });
}


void CameraSystem::pitchCameraUp() {
    auto cameras = (*m_registry).view<CameraComponent>();
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

void CameraSystem::pitchCameraDown() {
    auto cameras = (*m_registry).view<CameraComponent>();
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


void CameraSystem::yawCameraLeft() {
    auto cameras = (*m_registry).view<CameraComponent>();
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

void CameraSystem::yawCameraRight() {
    auto cameras = (*m_registry).view<CameraComponent>();
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

void CameraSystem::updateCameraVectors() {
    // retrieve a view of entities with applicable components
    auto cameras = (*m_registry).view<CameraComponent>();
    // iterate over each entity in the view
    cameras.each([&](auto& camera) {
        // calculate the new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        front.y = sin(glm::radians(camera.m_pitch));
        front.z = sin(glm::radians(camera.m_yaw)) * cos(glm::radians(camera.m_pitch));
        camera.m_front = glm::normalize(front);
        // also re-calculate the right and up vector
        // normalize - their length gets closer to 0 the more you look up 
        //  or down which results in slower movement
        camera.m_right = glm::normalize(glm::cross(camera.m_front, camera.m_worldUp));
        camera.m_up    = glm::normalize(glm::cross(camera.m_right, camera.m_front));
    });
}
