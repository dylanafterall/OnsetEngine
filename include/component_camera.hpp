// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_camera.hpp
//  header: component to hold camera data
// -----------------------------------------------------------------------------

#ifndef COMPONENT_CAMERA_H
#define COMPONENT_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct CameraComponent {
    float m_cameraSpeed;
    float m_yaw;
    float m_pitch;
    float m_sensitivity;
    float m_zoom;
    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f,  5.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
};

#endif // COMPONENT_CAMERA_H