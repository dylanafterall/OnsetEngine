// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.hpp
//  header: Render System to render textures on Box2D objects
// -----------------------------------------------------------------------------
#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include "component_body_circle.hpp"
#include "component_body_polygon.hpp"
#include "component_body_edge.hpp"
#include "component_body_chain.hpp"
#include "component_camera.hpp"
#include "component_mesh_cube.hpp"
#include "component_mesh_triangle.hpp"
#include "component_mesh_square.hpp"
#include "component_mesh_pentagon.hpp"
#include "component_mesh_hexagon.hpp"
#include "component_mesh_heptagon.hpp"
#include "component_mesh_octagon.hpp"
#include "component_render_buffers.hpp"
#include "component_shader.hpp"
#include "component_shader_program.hpp"
#include "component_texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "entt/entt.hpp"

class RenderSystem final {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void update(const float, entt::registry&, const unsigned int, const unsigned int);
    void deleteBuffers(entt::registry&);

private:

};

#endif // SYSTEM_RENDER_HPP
