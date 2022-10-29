// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_triangle.hpp
//  header: component to hold Box2D triangle shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_TRIANGLE_HPP
#define COMPONENT_SHAPE_TRIANGLE_HPP

#include "box2d/box2d.h"

//            (0)
//
//
//
//
//
//
//    (1)              (2)

struct ShapeTriangleComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[3];

    ShapeTriangleComponent() : m_vertexCount(3) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.866025f, -0.500000f);  // vertex (1)
        m_vertices[2].Set(0.866025f, -0.500000f);   // vertex (2)
    };
};

#endif // COMPONENT_SHAPE_TRIANGLE_HPP
