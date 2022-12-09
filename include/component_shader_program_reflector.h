// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader_program_reflector.h
//  header: component for shader program for recipient/reflector of light source
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_PROGRAM_REFLECTOR_H
#define COMPONENT_SHADER_PROGRAM_REFLECTOR_H

/** 
 * \brief   The ReflectorShaderProgramComponent struct.
 * \details A struct to hold data pertaining to OpenGL shader programs.
 */
struct ReflectorShaderProgramComponent {
    /**
     * \brief Unique OpenGL ID for a shader program (combination of a vertex and 
     *        fragment shader).
     */
    unsigned int m_shaderProgram;

    /**
     * \brief   The constructor.
     * \details Receives a shader program from AssetManager shaderPrograms map
     *          using getShaderProgram.
     */
    explicit ReflectorShaderProgramComponent(unsigned int shaderProgram) : 
        m_shaderProgram(shaderProgram) {
    }
};

#endif // COMPONENT_SHADER_PROGRAM_REFLECTOR_H