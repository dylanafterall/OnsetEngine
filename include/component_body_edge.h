// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_edge.h
//  header: component to hold Box2D edge bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_EDGE_H
#define COMPONENT_BODY_EDGE_H

#include "box2d/b2_body.h"
#include "box2d/box2d.h"


/** 
 * \brief   The BodyEdgeComponent struct.
 * \details A struct to hold data pertaining to Box2D Edge Bodies.
 */
struct BodyEdgeComponent {
    /**
     * \brief Holds all the Box2D data needed to construct a rigid body.
     */
    b2BodyDef m_bodyDef;
    /**
     * \brief Holds a Box2D rigid body ID.
     */
    b2Body* m_body;
    /**
     * \brief Holds a Box2D line segment (edge) shape. These can be connected 
     *        in chains or loops to other edge shapes.
     */
    b2EdgeShape m_edgeShape;
    /**
     * \brief Holds an abstract Box2D fixture definition, used to create a fixture.
     */
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_EDGE_H