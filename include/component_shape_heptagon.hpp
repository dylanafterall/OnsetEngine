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

    ShapeHeptagonComponent() : m_vertexCount(7) {
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
