// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_render_data.h
//  header: component to hold data pertinent to OpenGL rendering
// -----------------------------------------------------------------------------
#ifndef COMPONENT_RENDER_DATA_H
#define COMPONENT_RENDER_DATA_H

/** 
 * \brief   The RenderDataComponent struct.
 * \details A struct to hold data pertaining to OpenGL mesh vertex buffer and 
 *          array objects, plus other relevent data for OpenGL rendering. Passed 
 *          to RenderSystem class for rendering.
 */
struct RenderDataComponent {
    /**
     * \brief Unique OpenGL ID for a vertex buffer object.
     */
    unsigned int m_VBO; 
    /**
     * \brief Unique OpenGL ID for a vertex array object.
     */
    unsigned int m_VAO;
    /**
     * \brief The number of vertices constituting an object's mesh.
     */
    int m_vertexCount = 0;
    /**
     * \brief Boolean flag to set whether outline/stencil should be rendered.
     */
    bool m_stencilFlag = false;
};

#endif // COMPONENT_RENDER_DATA_H
