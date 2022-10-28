// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_test.hpp
//  header: component for troubleshooting render system
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHAPE_TEST_HPP
#define COMPONENT_SHAPE_TEST_HPP

#include "box2d/box2d.h"

struct ShapeTestComponent {
    float m_verticesRender[32] = {
        // positions            // colors           // texture coords
        0.5f,   0.5f,   0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f,   -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f,  -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,   0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int m_indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    ShapeTestComponent() {
    };
};

#endif // COMPONENT_SHAPE_TEST_HPP
