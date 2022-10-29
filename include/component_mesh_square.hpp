// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_square.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_SQUARE_HPP
#define COMPONENT_MESH_SQUARE_HPP

//             (0)
//
//
//
//    (1)               (3)
//
//
//
//             (2)

struct MeshSquareComponent {
    int m_indexCount;
    float m_vertices[32] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.497506f,  0.994684f,  // vertex (0)
        -1.000000f, 0.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.995794f,  0.502489f,  // vertex (1)
        0.000000f,  -1.000000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.502494f,  0.005316f,  // vertex (2)
        1.000000f,  0.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.004206f,  0.497511f   // vertex (3)
    };
    int m_indices[6] = {
        1, 0, 3,
        2, 1, 3
    };    

    MeshSquareComponent() : m_indexCount(6) {
    };
};

#endif // COMPONENT_MESH_SQUARE_HPP
