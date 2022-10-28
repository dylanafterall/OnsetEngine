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

    // for rendering system
    int m_indexCount;
    float m_verticesRender[40] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.994614f,  // vertex (0)
        -0.951057f, 0.309017f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.024049f,  0.648815f,  // vertex (1)
        -0.587785f, -0.809017f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.205846f,  0.089301f,  // vertex (2)
        0.587785f,  -0.809017f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.794154f,  0.089301f,  // vertex (3)
        0.951057f,  0.309017f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.975951f,  0.648815f   // vertex (4)
    };
    int m_indices[9] = {
        // for rendering, rotates CW - each line a triangle face (3 vertices)
        1, 0, 4,
        2, 1, 4,
        2, 4, 3
    };

    // vertex coordinates for a regular pentagon
    // centered at origin
    // for physics, rotates CCW
    ShapePentagonComponent() : m_vertexCount(5), m_indexCount(9) {
        m_vertices[0].Set(0.000000f, 1.000000f);    // vertex (0)
        m_vertices[1].Set(-0.951057f, 0.309017f);   // vertex (1)
        m_vertices[2].Set(-0.587785f, -0.809017f);  // vertex (2)
        m_vertices[3].Set(0.587785f, -0.809017f);   // vertex (3)
        m_vertices[4].Set(0.951057f, 0.309017f);    // vertex (4)
    };
};

#endif // COMPONENT_SHAPE_PENTAGON_HPP
