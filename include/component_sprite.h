// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_sprite.h
//  header: component to hold sprite data
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include "glm/glm.hpp"

/** 
 * \brief   The SpriteComponent struct.
 * \details A struct to hold data pertaining to mesh surface properties needed 
 *          in OpenGL rendering.
 */
struct SpriteComponent {
    /**
     * \brief Scalar value representing the degree of surface shininess (light 
     *        reflection).
     */
    float m_shininess;

    /**
     * \brief Vector to set position of sprite in game world (instead of using 
     *        a Box2D inactive body).
     */
    glm::vec3 m_position;

    /**
     * \brief Scalar to set rotation angle of sprite in game world (instead of 
     *        using a Box2D inactive body). In radians.
     */
    float m_rotation;

    /**
     * \brief Vector to set size of sprite in game world (instead of using 
     *        a Box2D inactive body).
     */
    glm::vec3 m_scale;
};

#endif // COMPONENT_SPRITE_H