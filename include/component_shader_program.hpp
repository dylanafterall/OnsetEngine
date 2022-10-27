// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader_program.hpp
//  header: component to hold shader program (two linked shaders)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_PROGRAM_HPP
#define COMPONENT_SHADER_PROGRAM_HPP

struct ShaderProgramComponent {
    unsigned int m_shaderProgram;

    // receive texture from AssetManager texture map using getTexture
    explicit ShaderProgramComponent(unsigned int shaderProgram) : 
        m_shaderProgram(shaderProgram) {
    }
};

#endif // COMPONENT_SHADER_PROGRAM_HPP
