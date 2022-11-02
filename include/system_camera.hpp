// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.hpp
//  header: system to control camera movement
// -----------------------------------------------------------------------------

#ifndef SYSTEM_CAMERA_HPP
#define SYSTEM_CAMERA_HPP

#include "entt/entt.hpp"

class CameraSystem {
public:
    CameraSystem() = default;
    ~CameraSystem() = default;

    void update(const float, entt::registry&);

private:

};

#endif // SYSTEM_CAMERA_HPP