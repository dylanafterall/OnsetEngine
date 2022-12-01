// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_render_buffers.h
//  header: component to hold openGL vbo, vao, and ebo buffer objects
// -----------------------------------------------------------------------------
#ifndef COMPONENT_RENDER_BUFFERS_H
#define COMPONENT_RENDER_BUFFERS_H

/** 
 * \brief   The RenderBuffersComponent struct.
 * \details A struct to hold data pertaining to OpenGL mesh vertex buffer and 
 *          array objects. Passed to RenderSystem class for rendering.
 */
struct RenderBuffersComponent {
    /**
     * \brief Unique OpenGL ID for a vertex buffer object.
     */
    unsigned int m_VBO; 
    /**
     * \brief Unique OpenGL ID for a vertex array object.
     */
    unsigned int m_VAO;
};

#endif // COMPONENT_RENDER_BUFFERS_H
