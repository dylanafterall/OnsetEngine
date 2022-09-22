// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_movement.hpp
//  header: Movement System to change positions of Box2D bodies
// -----------------------------------------------------------------------------
#ifndef SYSTEM_MOVEMENT_HPP
#define SYSTEM_MOVEMENT_HPP

#include "component_boxbody.hpp"

#include "entt/entt.hpp"

class MovementSystem final {
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void update(const float timeStep, entt::registry& registry);

private:

};

#endif // SYSTEM_MOVEMENT_HPP
