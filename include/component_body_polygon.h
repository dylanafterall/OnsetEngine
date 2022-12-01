// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_polygon.h
//  header: component to hold Box2D polygon bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_POLYGON_H
#define COMPONENT_BODY_POLYGON_H

#include "box2d/b2_body.h"
#include "box2d/box2d.h"


/** 
 * \brief   The BodyPolygonComponent struct.
 * \details A struct to hold data pertaining to Box2D Polygon Bodies.
 */
struct BodyPolygonComponent {
    /**
     * \brief Holds all the Box2D data needed to construct a rigid body.
     */
    b2BodyDef m_bodyDef;
    /**
     * \brief Holds a Box2D rigid body ID.
     */
    b2Body* m_body;
    /**
     * \brief Holds a Box2D solid convex polygon. Interior of the polygon is to 
     *        the left of each edge.
     */
    b2PolygonShape m_polygonShape;
    /**
     * \brief Holds an abstract Box2D fixture definition, used to create a fixture.
     */
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_POLYGON_H