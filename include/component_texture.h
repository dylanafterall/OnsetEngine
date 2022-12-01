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
     * \brief Unique OpenGL ID for a texture (imported via .png or .jpg asset).
     */
    unsigned int m_texture;

    /**
     * \brief   The constructor.
     * \details Receives a texture from AssetManager textures map using getTexture.
     */
    explicit TextureComponent(unsigned int texture) : m_texture(texture) {
    }
};

#endif // COMPONENT_TEXTURE_H
