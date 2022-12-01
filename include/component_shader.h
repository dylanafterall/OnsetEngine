// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_shader.h
//  header: component to hold shader ID  
// -----------------------------------------------------------------------------
#ifndef COMPONENT_SHADER_H
#define COMPONENT_SHADER_H

/** 
 * \brief   The ShaderComponent struct.
 * \details A struct to hold data pertaining to OpenGL shaders.
 */
struct ShaderComponent {
    /**
     * \brief Unique OpenGL ID for a vertex shader.
     */
    unsigned int m_vertexShader;
    /**
     * \brief Unique OpenGL ID for a fragment shader.
     */
    unsigned int m_fragmentShader;

    /**
     * \brief   The constructor.
     * \details Receives a vertex and fragment shader from AssetManager vshaders
     *          and fshaders maps, via getVShader and getFShader.
     */
    ShaderComponent(unsigned int vertexShader, unsigned int fragmentShader) :
        m_vertexShader(vertexShader), 
        m_fragmentShader(fragmentShader) {
    }
};

#endif // COMPONENT_SHADER_H
