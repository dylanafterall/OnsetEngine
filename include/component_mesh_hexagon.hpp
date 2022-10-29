// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_hexagon.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_HEXAGON_HPP
#define COMPONENT_MESH_HEXAGON_HPP

//            (0)
//
//    (1)             (5)
//  
//
//
//    (2)             (4)
//
//            (3)

struct MeshHexagonComponent {
    int m_indexCount;
    float m_vertices[48] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.994656f,  // vertex (0)
        -0.866025f, 0.500000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.064165f,  0.747328f,  // vertex (1)
        -0.866025f, -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.064165f,  0.252672f,  // vertex (2)
        0.000000f,  -1.000000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.005344f,  // vertex (3)
        0.866025f,  -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.935835f,  0.252672f,  // vertex (4)
        0.866025f,  0.500000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.935835f,  0.747328f   // vertex (5)
    };
    int m_indices[12] = {
        5, 0, 1,
        4, 5, 1,
        4, 1, 2,
        3, 4, 2
    };

    MeshHexagonComponent() : m_indexCount(12) {
    };
};

#endif // COMPONENT_MESH_HEXAGON_HPP
