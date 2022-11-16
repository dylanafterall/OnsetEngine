// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.h
//  header: system to control camera movement
// -----------------------------------------------------------------------------
#ifndef SYSTEM_CAMERA_H
#define SYSTEM_CAMERA_H

#include "component_camera.h"
#include "component_player.h"
#include "component_body_circle.h"
#include "component_body_polygon.h"

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

#endif // SYSTEM_CAMERA_H