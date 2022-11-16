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

struct BodyEdgeComponent {
    b2BodyDef m_bodyDef;
    b2Body* m_body;
    b2EdgeShape m_edgeShape;
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_EDGE_H