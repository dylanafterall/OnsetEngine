// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_movement.hpp
//  header: Movement System to change positions of Box2D bodies
// -----------------------------------------------------------------------------
#ifndef SYSTEM_MOVEMENT_HPP
#define SYSTEM_MOVEMENT_HPP

#include "component_body_circle.hpp"
#include "component_body_polygon.hpp"
#include "component_body_edge.hpp"
#include "component_body_chain.hpp"

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class MovementSystem final {
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void update(const float, entt::registry&);

private:

};

#endif // SYSTEM_MOVEMENT_HPP
