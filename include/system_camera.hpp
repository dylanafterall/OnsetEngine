// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.hpp
//  header: system to control camera movement
// -----------------------------------------------------------------------------

#ifndef SYSTEM_CAMERA_HPP
#define SYSTEM_CAMERA_HPP

#include "component_camera.hpp"
#include "component_player.hpp"
#include "component_body_circle.hpp"
#include "component_body_polygon.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

class CameraSystem {
public:
    CameraSystem() = default;
    ~CameraSystem() = default;

    void update(const float, entt::registry&);

private:
    void updateCameraVectors(entt::registry&);

};

#endif // SYSTEM_CAMERA_HPP