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

    // for rendering system
    float m_verticesRender[48] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.994656f,  // vertex (0)
        -0.866025f, 0.500000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.064165f,  0.747328f,  // vertex (1)
        -0.866025f, -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.064165f,  0.252672f,  // vertex (2)
        0.000000f,  -1.000000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.005344f,  // vertex (3)
        0.866025f,  -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.935835f,  0.252672f,  // vertex (4)
        0.866025f,  0.500000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.935835f,  0.747328f   // vertex (5)
    };
    int m_indices[12] = {
        // for rendering, rotates CW - each line a triangle face (3 vertices)
        5, 0, 1,
        4, 5, 1,
        4, 1, 2,
        3, 4, 2
    };

    // vertex coordinates for a regular hexagon
    // centered at origin
    // for physics, rotates CCW
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
