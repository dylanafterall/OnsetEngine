// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_polygon.hpp
//  header: component to hold Box2D polygon bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_POLYGON_HPP
#define COMPONENT_BODY_POLYGON_HPP

#include "box2d/b2_body.h"
#include "box2d/box2d.h"

struct BodyPolygonComponent {
    b2BodyDef m_bodyDef;
    b2Body* m_body;
    b2PolygonShape m_polygonShape;
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_POLYGON_HPP