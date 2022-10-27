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

    // for rendering system
    float m_verticesRender[64] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.991303f,  // vertex (0)
        -0.707107f, 0.707107f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.152596f,  0.847404f,  // vertex (1)
        -1.000000f, 0.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.008697f,  0.500000f,  // vertex (2)
        -0.707107f, -0.707107f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.152596f,  0.152596f,  // vertex (3)
        0.000000f,  -1.000000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.008697f,  // vertex (4)
        0.707107f,  -0.707107f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.847404f,  0.152596f,  // vertex (5)
        1.000000f,  0.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.991303f,  0.500000f,  // vertex (6)
        0.707107f,  0.707107f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.847404f,  0.847404f   // vertex (7)
    };
    int m_indices[18] = {
        // for rendering, rotates CW - each line a triangle face (3 vertices)
        7, 2, 0,
        2, 7, 6,
        3, 2, 6,
        3, 6, 5,
        4, 3, 5,
        2, 1, 0
    };

    // vertex coordinates for a regular octagon
    // centered at origin
    // for physics, rotates CCW
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
