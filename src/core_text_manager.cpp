// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_text_manager.cpp
//  implementation of class to handle text rendering 
// -----------------------------------------------------------------------------

#include "core_text_manager.h"

void TextManager::initialize(std::string fontName) {
    if (FT_Init_FreeType(&m_ft)) {
        ONSET_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
        return;
    }

    if (fontName.empty()) {
        ONSET_ERROR("ERROR::FREETYPE: Failed to locate {} from filesystem", fontName);
        return;
    }

    if (FT_New_Face(m_ft, fontName.c_str(), 0, &m_face)) {
        ONSET_ERROR("ERROR::FREETYPE: Failed to load {} font", fontName);
        return;
    }
    else {
        // set size to load glyphs as
        // setting width to 0 forces Face to dynamically calc width
        FT_Set_Pixel_Sizes(m_face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++) {
            // Load character glyph 
            if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
                ONSET_ERROR("ERROR::FREETYPE: Failed to load Glyph");
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                m_face->glyph->bitmap.width,
                m_face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                m_face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
                glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
                static_cast<unsigned int>(m_face->glyph->advance.x)
            };
            m_characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

Character TextManager::getCharacter(GLchar charID) {
    return m_characters[charID];
}

void TextManager::destroy() {
    for (auto character : m_characters) {
        glDeleteTextures(1, &character.second.m_textureID);
    }
    m_characters.clear();

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
}   