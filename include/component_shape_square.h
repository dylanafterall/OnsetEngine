// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_square.h
//  header: component to hold Box2D square shape (array of b2Vec2 vertices)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_SQUARE_H
#define COMPONENT_SHAPE_SQUARE_H

#include "box2d/box2d.h"

/** 
 * \brief   The ShapeSquareComponent struct.
 * \details A struct to hold data pertaining to square vertices, for use with 
 *          Box2D in creating a BodyPolygonComponent.
 */
struct ShapeSquareComponent {
    /**
     * \brief The number of vertices, for Box2D processing.
     */
    int32 m_vertexCount;
    /**
     * \brief An array of b2Vec2 vertices, constituting a 2D square.
     */
    b2Vec2 m_vertices[4];  

    /**
     * \brief   The constructor.
     * \details Creates a 2D square, centered on the origin (0.0f, 0.0f), with 
     *          area = 4.0f.
     */
    ShapeSquareComponent() : m_vertexCount(4) {
        m_vertices[0].Set(1.000000f, 1.000000f);    // top right 
        m_vertices[1].Set(-1.000000f, 1.000000f);   // top left
        m_vertices[2].Set(-1.000000f, -1.000000f);  // bottom left 
        m_vertices[3].Set(1.000000f, -1.000000f);   // bottom right 
    };
};

#endif // COMPONENT_SHAPE_SQUARE_H
