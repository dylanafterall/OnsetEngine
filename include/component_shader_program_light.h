// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader_program_light.h
//  header: shader programs for light reflection and depth mapping (shadows)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_PROGRAM_LIGHT_H
#define COMPONENT_SHADER_PROGRAM_LIGHT_H

/** 
 * \brief   The LightShaderProgramComponent struct.
 * \details A struct to hold data pertaining to OpenGL shader programs.
 */
struct LightShaderProgramComponent {
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) for rendering light reflection.
     */
    unsigned int m_reflectorProgram;
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader) for rendering a depth map to a FBO.
     */
    unsigned int m_depthMapProgram;
};

#endif // COMPONENT_SHADER_PROGRAM_LIGHT_H