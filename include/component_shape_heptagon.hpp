// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_heptagon.hpp
//  header: component to hold Box2D heptagon shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_HEPTAGON_HPP
#define COMPONENT_SHAPE_HEPTAGON_HPP

#include "box2d/box2d.h"

//               (0)
//
//       (1)             (6)
//    
//
//
//    (2)                    (5)
//
//
//           (3)     (4)

struct ShapeHeptagonComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[7];

    // for rendering system
    int m_indexCount;
    float m_verticesRender[56] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.989487f,  // vertex (0)
        -0.781832f, 0.623490f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.105565f,  0.802104f,  // vertex (1)
        -0.974928f, -0.222521f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.008148f,  0.381057f,  // vertex (2)
        -0.433884f, -0.900969f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.281105f,  0.043404f,  // vertex (3)
        0.433884f,  -0.900969f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.718895f,  0.043404f,  // vertex (4)
        0.974928f,  -0.222521f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.991852f,  0.381057f,  // vertex (5)
        0.781832f,  0.623490f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.894435f,  0.802104f   // vertex (6)
    };
    int m_indices[15] = {
        // for rendering, rotates CW - each line a triangle face (3 vertices)
        6, 0, 1,
        5, 6, 1,
        5, 1, 2,
        4, 5, 2,
        4, 2, 3
    };

    // vertex coordinates for a regular heptagon
    // centered at origin
    // for physics, rotates CCW
    ShapeHeptagonComponent() : m_vertexCount(7), m_indexCount(15) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.781832f, 0.623490f);   // vertex (1)
        m_vertices[2].Set(-0.974928f, -0.222521f);  // vertex (2)
        m_vertices[3].Set(-0.433884f, -0.900969f);  // vertex (3)
        m_vertices[4].Set(0.433884f, -0.900969f);   // vertex (4)
        m_vertices[5].Set(0.974928f, -0.222521f);   // vertex (5)
        m_vertices[6].Set(0.781832f, 0.623490f);    // vertex (6)
    };
};

#endif // COMPONENT_SHAPE_HEPTAGON_HPP
