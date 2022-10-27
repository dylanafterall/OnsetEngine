// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_circle.hpp
//  header: component to hold Box2D circle bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_CIRCLE_HPP
#define COMPONENT_BODY_CIRCLE_HPP

#include "box2d/b2_body.h"
#include "box2d/box2d.h"

struct BodyCircleComponent {
    b2BodyDef m_bodyDef;
    b2Body* m_body;
    b2CircleShape m_circleShape;
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_CIRLCE_HPP