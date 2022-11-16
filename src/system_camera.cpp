// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.cpp
//  system to control camera movement
// -----------------------------------------------------------------------------

#include "system_camera.hpp"

void CameraSystem::update(const float timeStep, entt::registry& registry) {
    // get the player position, in order to provide translate transform to camera
    glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f);
    auto player = registry.view<
        PlayerComponent,
        BodyCircleComponent
    >();
    player.each([&](
        auto& player,
        auto& body
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        translate[0] = position.x;
        translate[1] = position.y;
    });

    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](auto& camera) {
        camera.m_position[0] = translate[0];
        camera.m_position[1] = translate[1];
    });
}

// updateCameraVectors(): calculates the front vector from updated Euler Angles
void CameraSystem::updateCameraVectors(entt::registry& registry) {
    // retrieve a view of entities with applicable components
    auto cameras = registry.view<CameraComponent>();
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
