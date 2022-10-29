// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_pentagon.hpp
//  header: component to hold Box2D pentagon shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_PENTAGON_HPP
#define COMPONENT_SHAPE_PENTAGON_HPP

#include "box2d/box2d.h"

//            (0)
//
//
//    (1)             (4)
//
//
//
//        (2)     (3)

struct ShapePentagonComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[5];

    ShapePentagonComponent() : m_vertexCount(5) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.951057f, 0.309017f);   // vertex (1)
        m_vertices[2].Set(-0.587785f, -0.809017f);  // vertex (2)
        m_vertices[3].Set(0.587785f, -0.809017f);   // vertex (3)
        m_vertices[4].Set(0.951057f, 0.309017f);    // vertex (4)
    };
};

#endif // COMPONENT_SHAPE_PENTAGON_HPP
