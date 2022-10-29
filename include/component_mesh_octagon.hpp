// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_octagon.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_OCTAGON_HPP
#define COMPONENT_MESH_OCTAGON_HPP

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

struct MeshOctagonComponent {
    int m_indexCount;
    float m_vertices[64] = {
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
        7, 2, 0,
        2, 7, 6,
        3, 2, 6,
        3, 6, 5,
        4, 3, 5,
        2, 1, 0
    };

    MeshOctagonComponent() : m_indexCount(18) {
    };
};

#endif // COMPONENT_MESH_OCTAGON_HPP
