// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.h
//  header: Render System to render textures on Box2D objects
// -----------------------------------------------------------------------------
#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include "component_body_transform.h"
#include "component_camera.h"
#include "component_light.h"
#include "component_material.h"
#include "component_render_data.h"
#include "component_shader.h"
#include "component_shader_program.h"
#include "component_shader_program_reflector.h"
#include "component_skybox.h"
#include "component_sprite.h"
#include "component_texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "entt/entt.hpp"

#include <string>

/** 
 * \brief   The RenderSystem class.
 * \details Used by Game class to render objects via OpenGL API.
 */
class RenderSystem final {
public:
    /**
     * \brief   The default constructor. 
     */
    RenderSystem() = default;
    /**
     * \brief   The default destructor. 
     */
    ~RenderSystem() = default;

    /**
     * \brief   The function update. 
     * \details This function renders selected entities to the game's glfw 
     *          window. Uses Box2D bodies for position and angle of rendered
     *          output, and OpenGL IDs for textures, shaders, and vertex 
     *          buffers/arrays.
     * \param   timeStep    The amount of time to simulate (representing seconds).
     * \param   registry    The game's EnTT registry for accessing renderable entities.
     * \param   SCR_WIDTH   The game window's width for aspect ratio.
     * \param   SCR_HEIGHT  The game window's height for aspect ratio.
     * \return  void, none.
     */
    void update(const float, entt::registry&, const unsigned int, const unsigned int);
    /**
     * \brief   The function deleteBuffers. 
     * \details This function deletes the OpenGL VBO and VAO buffers from memory for
     *          selected entities (those with a RenderBuffersComponent).
     * \param   registry    The game's EnTT registry for accessing renderable entities.
     * \return  void, none.
     */
    void deleteBuffers(entt::registry&);
};

#endif // SYSTEM_RENDER_H