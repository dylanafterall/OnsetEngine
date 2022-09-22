// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_boxbody.hpp
//  header: component to hold box2d bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BOXBODY_HPP
#define COMPONENT_BOXBODY_HPP

#include "box2d/b2_body.h"
#include "box2d/box2d.h"

struct BoxBodyComponent {
    b2BodyDef m_bodyDef;
    b2Body* m_body;
    b2PolygonShape m_polygonShape;
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BOXBODY_HPP
