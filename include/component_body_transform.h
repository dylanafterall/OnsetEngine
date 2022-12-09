// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_transform.h
//  header: component to hold Box2D polygon body data pertaining to transforms
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_TRANSFORM_H
#define COMPONENT_BODY_TRANSFORM_H

#include "box2d/b2_body.h"
#include "box2d/box2d.h"

/** 
 * \brief   The BodyTransformComponent struct.
 * \details A struct to hold data pertaining to Box2D Polygon Bodies. Only 
 *          stores data pertinent to rendering, like position and rotation, 
 *          and not body fixture information.
 */
struct BodyTransformComponent {
    /**
     * \brief Holds a Box2D rigid body ID.
     */
    b2Body* m_body;
};

#endif // COMPONENT_BODY_TRANSFORM_H