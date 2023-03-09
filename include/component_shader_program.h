// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader_program.h
//  header: component to hold shader program (two linked shaders)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_PROGRAM_H
#define COMPONENT_SHADER_PROGRAM_H

/** 
 * \brief   The ShaderProgramComponent struct.
 * \details A struct to hold data pertaining to OpenGL shader programs.
 */
struct ShaderProgramComponent {
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader).
     */
    unsigned int m_outputProgram;
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) for rendering light reflection.
     */
    unsigned int m_lightProgram;
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) for surfaces in a shadow FBO depth map.
     */
    unsigned int m_shadowProgram;
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) specifically used in outlining/stenciling an 
     *        object when rendering.
     */
    unsigned int m_stencilProgram;
};

#endif // COMPONENT_SHADER_PROGRAM_H
