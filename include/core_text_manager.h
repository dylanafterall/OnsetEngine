// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_text_manager.h
//  header: class to load and render text characters to window, using FreeType
// -----------------------------------------------------------------------------
#ifndef CORE_TEXT_MANAGER_H
#define CORE_TEXT_MANAGER_H

#include "ft2build.h"
#include FT_FREETYPE_H 
#include "core_log_macros.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <map>

/** 
 * \brief   The Character struct.
 * \details Holds all state information relevant to a character as loaded using 
 *          FreeType.
 */
struct Character {
    /**
     * \brief ID handle of the glyph texture.
     */
    unsigned int m_textureID;
    /**
     * \brief Size of glyph.
     */
    glm::ivec2 m_size;
    /**
     * \brief Offset from baseline to left/top of glyph.
     */
    glm::ivec2 m_bearing;
    /**
     * \brief Horizontal offset to advance to next glyph.
     */
    unsigned int m_advance;
};

/** 
 * \brief   The TextManager class.
 * \details Used by Game class to load and render text characters to window.
 */
class TextManager final {
public:
    /**
     * \brief   The default constructor. 
     */
    TextManager() = default;
    /**
     * \brief   The default destructor. 
     */
    ~TextManager() = default;

    /**
     * \brief   The function initialize. 
     * \details This function initializes the FreeType library, loading the 
     *          provided texture fonts.
     * \return  void, none.
     */
    void initialize(std::string);

    /**
     * \brief   The function getCharacter. 
     * \details This function returns a Character struct with data for 
     *          ID, size, bearing, and advance for a FreeType character.
     * \param   charID      The key to search the characters map for.
     * \retval  character   A Character struct with data necessary for rendering
     *                      the requested character.
     */
    Character getCharacter(GLchar);

    /**
     * \brief   The function destroy. 
     * \details This function frees memory allocated by FreeType library.
     * \return  void, none.
     */
    void destroy();

private:
    /**
     * \brief FreeType library to be initialized for text character rendering.
     */
    FT_Library m_ft;
    /**
     * \brief FreeType face with an associated font.
     */
    FT_Face m_face;

    /**
     * \brief std::map used to store text character information.
     */
    std::map<GLchar, Character> m_characters;
};

#endif // CORE_TEXT_MANGER_H