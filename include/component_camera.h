// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_camera.h
//  header: component to hold camera data
// -----------------------------------------------------------------------------

#ifndef COMPONENT_CAMERA_H
#define COMPONENT_CAMERA_H

#include "glm/glm.hpp"

// default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  1.0f;
const float SENSITIVITY =  1.0f;
const float ZOOM        =  45.0f;

struct CameraComponent {
    // euler angles
    float m_yaw;
    float m_pitch;
    // camera options
    float m_speed;
    float m_sensitivity;
    float m_zoom;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    // constructor
    CameraComponent(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 20.0f), 
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = YAW, 
        float pitch = PITCH
    ) : m_speed(SPEED), 
        m_sensitivity(SENSITIVITY), 
        m_zoom(ZOOM),
        m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        m_position = position;
        m_worldUp = worldUp;
        m_yaw = yaw;
        m_pitch = pitch;

        // update vectors
        // calculate the new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
        // also re-calculate the right and up vector
        // normalize - their length gets closer to 0 the more you look up 
        //  or down which results in slower movement
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up    = glm::normalize(glm::cross(m_right, m_front));
    }
};

#endif // COMPONENT_CAMERA_H