// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader.hpp
//  header: component to hold shader ID  
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_HPP
#define COMPONENT_SHADER_HPP

struct ShaderComponent {
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;

    // receive shaders from AssetManager shader maps, getVShader and getFShader
    ShaderComponent(unsigned int vertexShader, unsigned int fragmentShader) :
        m_vertexShader(vertexShader), 
        m_fragmentShader(fragmentShader) {
    }
};

#endif // COMPONENT_SHADER_HPP
