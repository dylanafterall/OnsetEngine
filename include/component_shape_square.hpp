// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_square.hpp
//  header: component to hold Box2D square shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_SQUARE_HPP
#define COMPONENT_SHAPE_SQUARE_HPP

#include "box2d/box2d.h"

//             (0)
//
//
//
//    (1)               (3)
//
//
//
//             (2)

struct ShapeSquareComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[4];  

    ShapeSquareComponent() : m_vertexCount(4) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-1.000000f, 0.000000f);   // vertex (1)
        m_vertices[2].Set(0.000000f, -1.000000f);   // vertex (2)
        m_vertices[3].Set(1.000000f, 0.000000f);    // vertex (3)
    };
};

#endif // COMPONENT_SHAPE_SQUARE_HPP
