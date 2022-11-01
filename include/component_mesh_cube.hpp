// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_cube.hpp
//  header: component to hold vertex and index data for OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_MESH_CUBE_HPP
#define COMPONENT_MESH_CUBE_HPP

//        ()----------()    
//       /           / |
//    ()----------()   |
//    |            |   |
//    |            |  ()
//    |            | /
//    ()----------()        

struct MeshCubeComponent {
    int m_indexCount;
    float m_vertices[64] = {
        // positions x y z                  // colors r g b     // tex coords u v
        1.000000f,  1.000000f,  -1.000000f, 1.0f, 1.0f, 1.0f,   0.497506f,  0.994684f,
        1.000000f,  -1.000000f, -1.000000f, 1.0f, 1.0f, 1.0f,   0.995794f,  0.502489f,
        1.000000f,  1.000000f,  1.000000f,  1.0f, 1.0f, 1.0f,   0.502494f,  0.005316f,
        1.000000f,  -1.000000f, 1.000000f,  1.0f, 1.0f, 1.0f,   0.004206f,  0.497511f,
        -1.000000f, 1.000000f,  -1.000000f, 1.0f, 1.0f, 1.0f,   0.497506f,  0.994684f,
        -1.000000f, -1.000000f, -1.000000f, 1.0f, 1.0f, 1.0f,   0.995794f,  0.502489f,
        -1.000000f, 1.000000f,  1.000000f,  1.0f, 1.0f, 1.0f,   0.502494f,  0.005316f,
        -1.000000f, -1.000000f, 1.000000f,  1.0f, 1.0f, 1.0f,   0.004206f,  0.497511f
    };
    int m_indices[36] = {
        4, 2, 0,
        2, 7, 3,
        6, 5, 7,
        1, 7, 5,
        0, 3, 1,
        4, 1, 5,
        4, 6, 2,
        2, 6, 7,
        6, 4, 5,
        1, 3, 7,
        0, 2, 3,
        4, 0, 1
    };    

    MeshCubeComponent() : m_indexCount(36) {
    };
};

#endif // COMPONENT_MESH_CUBE_HPP