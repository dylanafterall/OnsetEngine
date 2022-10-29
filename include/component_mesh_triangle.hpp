// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_triangle.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_TRIANGLE_HPP
#define COMPONENT_MESH_TRIANGLE_HPP

//            (0)
//
//
//
//
//
//
//    (1)              (2)

struct MeshTriangleComponent {
    int m_indexCount;
    float m_vertices[24] = {
        // positions x y z                  // colors r g b     // tex coords u v
        0.000000f,  1.000000f,  0.000000f,  1.0f, 1.0f, 1.0f,   0.500000f,  0.996495f,  // vertex (0)
        -0.866025f, -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.063021f,  0.239624f,  // vertex (1)
        0.866025f,  -0.500000f, 0.000000f,  1.0f, 1.0f, 1.0f,   0.936979f,  0.239624f   // vertex (2)
    };
    int m_indices[3] = {
        1, 0, 2
    };

    MeshTriangleComponent() : m_indexCount(3) {
    };
};

#endif // COMPONENT_MESH_TRIANGLE_HPP
