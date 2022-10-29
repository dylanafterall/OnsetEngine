// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_pentagon.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_PENTAGON_HPP
#define COMPONENT_MESH_PENTAGON_HPP

//            (0)
//
//
//    (1)             (4)
//
//
//
//        (2)     (3)

struct MeshPentagonComponent {
    int m_indexCount;
    float m_vertices[40] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.994614f,  // vertex (0)
        -0.951057f, 0.309017f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.024049f,  0.648815f,  // vertex (1)
        -0.587785f, -0.809017f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.205846f,  0.089301f,  // vertex (2)
        0.587785f,  -0.809017f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.794154f,  0.089301f,  // vertex (3)
        0.951057f,  0.309017f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.975951f,  0.648815f   // vertex (4)
    };
    int m_indices[9] = {
        1, 0, 4,
        2, 1, 4,
        2, 4, 3
    };

    MeshPentagonComponent() : m_indexCount(9) {
    };
};

#endif // COMPONENT_MESH_PENTAGON_HPP
