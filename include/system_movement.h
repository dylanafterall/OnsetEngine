// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_movement.h
//  header: Movement System to change positions of Box2D bodies
// -----------------------------------------------------------------------------
#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "component_body_circle.h"
#include "component_body_polygon.h"
#include "component_body_edge.h"
#include "component_body_chain.h"

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

#endif // SYSTEM_MOVEMENT_H