// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_octagon.hpp
//  header: component to hold Box2D octagon shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_OCTAGON_HPP
#define COMPONENT_SHAPE_OCTAGON_HPP

#include "box2d/box2d.h"

//                 (0)
//
//        (1)                (7)
//
//
//
//     (2)                       (6)
//        
//
//
//        (3)                (5)
//
//                 (4)

struct ShapeOctagonComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[8];

    ShapeOctagonComponent() : m_vertexCount(8) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.707107f, 0.707107f);   // vertex (1)
        m_vertices[2].Set(-1.000000f, 0.000000f);   // vertex (2)
        m_vertices[3].Set(-0.707107f, -0.707107f);  // vertex (3)
        m_vertices[4].Set(0.000000f, -1.000000f);   // vertex (4)
        m_vertices[5].Set(0.707107f, -0.707107f);   // vertex (5)
        m_vertices[6].Set(1.000000f, 0.000000f);    // vertex (6)
        m_vertices[7].Set(0.707107f, 0.707107f);    // vertex (7)
    };
};

#endif // COMPONENT_SHAPE_OCTAGON_HPP
