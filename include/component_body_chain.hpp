// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_body_chain.hpp
//  header: component to hold Box2D chain bodies
// -----------------------------------------------------------------------------
#ifndef COMPONENT_BODY_CHAIN_HPP
#define COMPONENT_BODY_CHAIN_HPP

#include "box2d/b2_body.h"
#include "box2d/box2d.h"

struct BodyChainComponent {
    b2BodyDef m_bodyDef;
    b2Body* m_body;
    b2ChainShape m_chainShape;
    b2FixtureDef m_fixtureDef;
};

#endif // COMPONENT_BODY_CHAIN_HPP