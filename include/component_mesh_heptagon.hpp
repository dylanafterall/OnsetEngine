// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shape_mesh.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_HEPTAGON_HPP
#define COMPONENT_MESH_HEPTAGON_HPP

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

struct MeshHeptagonComponent {
    int m_indexCount;
    float m_vertices[56] = {
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
        6, 0, 1,
        5, 6, 1,
        5, 1, 2,
        4, 5, 2,
        4, 2, 3
    };

    MeshHeptagonComponent() : m_indexCount(15) {
    };
};

#endif // COMPONENT_MESH_HEPTAGON_HPP
