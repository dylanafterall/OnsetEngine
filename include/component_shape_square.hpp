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

struct ShapeSquareComponent {
    // for physics engine
    int32 m_vertexCount;
    b2Vec2 m_vertices[4];  

    ShapeSquareComponent() : m_vertexCount(4) {
        m_vertices[0].Set(1.000000f, 1.000000f);    // top right 
        m_vertices[1].Set(-1.000000f, 1.000000f);   // top left
        m_vertices[2].Set(-1.000000f, -1.000000f);  // bottom left 
        m_vertices[3].Set(1.000000f, -1.000000f);   // bottom right 
    };
};

#endif // COMPONENT_SHAPE_SQUARE_HPP
