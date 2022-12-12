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

/**
 * \brief Camera type - for specifying which camera to act on.
 */
enum CameraType{first=1, second, third};

/**
 * \brief Default camera yaw value.
 */
const float YAW         = -90.0f;
/**
 * \brief Default camera pitch value.
 */
const float PITCH       =  0.0f;
/**
 * \brief Default camera speed value.
 */
const float SPEED       =  1.0f;
/**
 * \brief Default camera sensitivity value.
 */
const float SENSITIVITY =  1.0f;
/**
 * \brief Default camera zoom value.
 */
const float ZOOM        =  45.0f;

/** 
 * \brief   The CameraComponent struct.
 * \details A struct to hold data pertaining to the game's camera.
 */
struct CameraComponent {
    /**
     * \brief Camera type, 1=first, 2=second, 3=third.
     */
    CameraType m_type;

    /**
     * \brief Camera yaw (euler angle) value member variable. Scalar.
     */
    float m_yaw;
    /**
     * \brief Camera pitch (euler angle) value member variable. Scalar.
     */
    float m_pitch;
    
    /**
     * \brief Camera speed value member variable. Scalar.
     */
    float m_speed;
    /**
     * \brief Camera sensitivity value member variable. Scalar.
     */
    float m_sensitivity;
    /**
     * \brief Camera zoom value member variable. Scalar.
     */
    float m_zoom;

    /**
     * \brief Camera position value member variable. Vector.
     */
    glm::vec3 m_position;
    /**
     * \brief Camera front direction value member variable. Vector.
     */
    glm::vec3 m_front;
    /**
     * \brief Camera up direction value member variable. Vector.
     */
    glm::vec3 m_up;
    /**
     * \brief Camera right direction value member variable. Vector.
     */
    glm::vec3 m_right;
    /**
     * \brief World up direction value member variable. Vector.
     */
    glm::vec3 m_worldUp;

    /**
     * \brief   The constructor. 
     * \details This function sets camera member variables and updates the
     *          camera vectors (m_front, m_right, and m_up) based on 
     *          values provided / defaulted. 
     * \param   position    Camera position in world space, vector. 
     * \param   worldUp     World up direction, vector. 
     * \param   yaw         Camera yaw (euler) angle, scalar. 
     * \param   pitch       Camera pitch (euler) angle, scalar. 
     */
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