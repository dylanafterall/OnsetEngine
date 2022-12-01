// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_chain.h
//  header: component to hold Box2D chain bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_CHAIN_H
#define COMPONENT_BODY_CHAIN_H

#include "box2d/b2_body.h"
#include "box2d/box2d.h"


/** 
 * \brief   The BodyChainComponent struct.
 * \details A struct to hold data pertaining to Box2D Chain Bodies.
 */
struct BodyChainComponent {
    /**
     * \brief Holds all the Box2D data needed to construct a rigid body.
     */
    b2BodyDef m_bodyDef;
    /**
     * \brief Holds a Box2D rigid body ID.
     */
    b2Body* m_body;
    /**
     * \brief Holds a Box2D free form sequence of line segments. The chain has 
     *        one-sided collision, with the surface normal pointing to the 
     *        right of the edge. This provides a counter-clockwise winding like 
     *        the polygon shape. Connectivity information is used to create 
     *        smooth collisions.
     */
    b2ChainShape m_chainShape;
    /**
     * \brief Holds an abstract Box2D fixture definition, used to create a fixture.
     */
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_CHAIN_H