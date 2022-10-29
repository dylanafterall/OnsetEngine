// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_hexagon.hpp
//  header: component to hold Box2D hexagon shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_HEXAGON_HPP
#define COMPONENT_SHAPE_HEXAGON_HPP

#include "box2d/box2d.h"

//            (0)
//
//    (1)             (5)
//  
//
//
//    (2)             (4)
//
//            (3)

struct ShapeHexagonComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[6];

    ShapeHexagonComponent() : m_vertexCount(6) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.866025f, 0.500000f);   // vertex (1)
        m_vertices[2].Set(-0.866025f, -0.500000f);  // vertex (2)
        m_vertices[3].Set(0.000000f, -1.000000f);   // vertex (3)
        m_vertices[4].Set(0.866025f, -0.500000f);   // vertex (4)
        m_vertices[5].Set(0.866025f, 0.500000f);    // vertex (5)
    };
};

#endif // COMPONENT_SHAPE_HEXAGON_HPP
