// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_texture.h
//  header: component to hold texture1 and texture2 
// -----------------------------------------------------------------------------
#ifndef COMPONENT_TEXTURE_H
#define COMPONENT_TEXTURE_H

/** 
 * \brief   The TextureComponent struct.
 * \details A struct to hold data pertaining to OpenGL textures.
 */
struct TextureComponent {
    /**
     * \brief Unique OpenGL ID for a texture (texture map - diffuse).
     */
    unsigned int m_diffuse;
    /**
     * \brief Unique OpenGL ID for a texture (texture map - specular).
     */
    unsigned int m_specular;
    /**
     * \brief Unique OpenGL ID for a cubemap.
     */
    unsigned int m_cubemap;

    /**
     * \brief   The constructor.
     * \details Constructor without textures passed as parameters.
     */
    TextureComponent() {}

    /**
     * \brief   The constructor.
     * \details Receives textures from AssetManager textures map using getTexture.
     */
    TextureComponent(unsigned int diffuse, unsigned int specular) {
        m_diffuse = diffuse;
        m_specular = specular;
    }
};

#endif // COMPONENT_TEXTURE_H
