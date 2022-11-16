// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.h
//  header: Render System to render textures on Box2D objects
// -----------------------------------------------------------------------------
#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include "component_body_circle.h"
#include "component_body_polygon.h"
#include "component_body_edge.h"
#include "component_body_chain.h"
#include "component_camera.h"
#include "meshes/component_mesh_cube.h"
#include "meshes/component_mesh_ground.h"
#include "meshes/component_mesh_sphere.h"
#include "component_render_buffers.h"
#include "component_shader.h"
#include "component_shader_program.h"
#include "component_texture.h"

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

#endif // SYSTEM_RENDER_H