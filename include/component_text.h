// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_text.h
//  header: component to hold data pertaining to text (to be rendered)
// -----------------------------------------------------------------------------
#ifndef COMPONENT_TEXT_H
#define COMPONENT_TEXT_H

#include "core_text_manager.h"

/** 
 * \brief   The TextComponent struct.
 * \details A struct to hold data pertaining to characters to be rendered via 
 *          the FreeType library.
 */
struct TextComponent {
    /**
     * \brief A vector of the FreeType character data needed for text rendering.
     */
    std::vector<Character> m_characters;

    /**
     * \brief X coordinate of screen location to render text.
     */
    float m_xCoord;
    /**
     * \brief Y coordinate of screen location to render text.
     */
    float m_yCoord;
    /**
     * \brief Scale factor to determine size of text to be rendered.
     */
    float m_scale;
    /**
     * \brief Color values (r/g/b) of text to be rendered.
     */
    glm::vec3 m_color;
};

#endif // COMPONENT_TEXT_H