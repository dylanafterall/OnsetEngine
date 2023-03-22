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
#include "component_shadow_framebuffer.h"
#include "component_skybox.h"
#include "component_sprite.h"
#include "component_test.h"
#include "component_text.h"
#include "component_texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
     * \param   camera      A pointer to the game's camera inside the registry.
     * \return  void, none.
     */
    void update(const float, entt::registry&);
    /**
     * \brief   The function deleteBuffers. 
     * \details This function deletes the OpenGL VBO and VAO buffers from memory for
     *          selected entities (those with a RenderBuffersComponent).
     * \param   registry    The game's EnTT registry for accessing renderable entities.
     * \return  void, none.
     */
    void deleteBuffers(entt::registry&);
    /**
     * \brief   The function setGammaFlag. 
     * \details This function sets the Render System's GammaFlag, which determines
     *          whether gamma correction will be applied by OpenGL.
     * \param   gamma    Boolean representing if gamma correction is enabled (true).
     * \return  void, none.
     */
    void setGammaFlag(bool);
    /**
     * \brief   The function setShadowResolution. 
     * \details This function sets the Render System's m_shadowWidth and m_shadowHeight, 
     *          which sets the resolution of shadow maps.
     * \param   unsigned int    shadowWidth     Sets the width of shadow map resolution.
     * \param   unsigned int    shadowHeight    Sets the height of shadow map resolution.
     * \return  void, none.
     */
    void setShadowResolution(unsigned int, unsigned int);
    /**
     * \brief   The function setWindowPointer. 
     * \details This function sets the Render System's m_glfwWindow, which will be used 
     *          for getting window size and framebuffer size when needed for rendering.
     * \param   GLFWwindow*    glfwWindow     Pointer to the game's GLFW window.
     * \return  void, none.
     */
    void setWindowPointer(GLFWwindow*);
    /**
     * \brief   The function handleFramebufferResize. 
     * \details This function processes user changing the glfw window size. Will 
     *          be used to then adjust framebuffer accordingly.
     * \param   window      Pointer to the glfw window being resized.
     * \param   width       Width of the framebuffer after window resize.
     * \param   height      Height of the framebuffer after window resize.
     * \return  void, none.
     */
    void handleFramebufferResize(GLFWwindow*, int, int);

private:
    /**
     * \brief Pointer to game's GLFW generated window.
     */
    GLFWwindow* m_glfwWindow;
    /**
     * \brief Boolean to represent whether gamma correction is enabled for rendering.
     */
    bool m_gammaFlag = true;
    /**
     * \brief Integer to represent the Width of the glfw window.
     */
    int m_screenWidth;
    /**
     * \brief Integer to represent the Height of the glfw window.
     */
    int m_screenHeight;

    /**
     * \brief Integer to represent the Width of depth map (for shadow resolution).
     */
    unsigned int m_shadowWidth;
    /**
     * \brief Integer to represent the Height of depth map (for shadow resolution).
     */
    unsigned int m_shadowHeight;
};

#endif // SYSTEM_RENDER_H