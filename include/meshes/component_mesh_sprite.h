// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_mesh_sprite.h
//  component to hold vertex (x,y,z / i,j,k / u,v) data for OpenGL rendering 
// -----------------------------------------------------------------------------

#ifndef COMPONENT_MESH_SPRITE_H
#define COMPONENT_MESH_SPRITE_H

struct MeshSpriteComponent { 
    float m_vertices[30] = { 
        // position (x y z)  // texture (u v)
        -1.0f,  1.0f,   0.0f,   0.0f,   0.0f,
        -1.0f,  -1.0f,  0.0f,   0.0f,   1.0f,
        1.0f,   -1.0f,  0.0f,   1.0f,   1.0f,

        -1.0f,  1.0f,   0.0f,   0.0f,   0.0f,
        1.0f,   -1.0f,  0.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   0.0f,   1.0f,   0.0f
    };

    int m_verticesSize = 120;

    int m_vertexCount = 6;

};

#endif // COMPONENT_MESH_SPRITE_H