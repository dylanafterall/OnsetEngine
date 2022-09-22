// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.hpp
//  header: Render System to render textures on Box2D objects
// -----------------------------------------------------------------------------
#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include "component_boxbody.hpp"
#include "component_shader.hpp"
#include "component_shaderprogram.hpp"
#include "component_texture.hpp"

#include "entt/entt.hpp"

class RenderSystem final {
public:
    RenderSystem() = default;
    ~RenderSystem() = default;

    void update(const float timeStep, entt::registry& registry);

private:

};

#endif // SYSTEM_RENDER_HPP
