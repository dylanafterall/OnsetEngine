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
#include "component_render_buffers.hpp"
#include "component_shader.hpp"
#include "component_shader_program.hpp"
#include "component_shape_triangle.hpp"
#include "component_shape_square.hpp"
#include "component_shape_pentagon.hpp"
#include "component_shape_hexagon.hpp"
#include "component_shape_heptagon.hpp"
#include "component_shape_octagon.hpp"
#include "component_texture.hpp"

#include "entt/entt.hpp"
#include "box2d/box2d.h"

class RenderSystem final {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void update(const float timeStep, entt::registry& registry);

private:

};

#endif // SYSTEM_RENDER_HPP
