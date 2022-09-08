// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_texture.hpp
//  header: component to hold texture1 and texture2 
// -----------------------------------------------------------------------------
#ifndef COMPONENT_TEXTURE_HPP
#define COMPONENT_TEXTURE_HPP

struct TextureComponent {
    unsigned int m_texture;

    // receive texture from AssetManager texture map using getTexture
    explicit TextureComponent(unsigned int texture) {
        m_texture = texture;
    }
};

#endif // COMPONENT_TEXTURE_HPP
