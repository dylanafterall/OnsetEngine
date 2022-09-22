// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_movement.cpp
//  implementation of Movement System to change positions of Box2D bodies
// -----------------------------------------------------------------------------

#include "system_movement.hpp"

void MovementSystem::update(const float timeStep, entt::registry& registry) {
    // retrieve a view of entities with the BoxBodyComponent
    auto view = registry.view<BoxBodyComponent>();
    // iterate over each entity in the view
    view.each([&](const auto& box) {
        b2Vec2 position = box.m_body->GetPosition();
        float angle = box.m_body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);       
    });
}
