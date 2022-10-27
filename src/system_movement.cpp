// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_movement.cpp
//  implementation of Movement System to change positions of Box2D bodies
// -----------------------------------------------------------------------------

#include "system_movement.hpp"

void MovementSystem::update(const float timeStep, entt::registry& registry) {
    // retrieve a view of entities with the BodyPolygonComponent
    auto polygons = registry.view<BodyPolygonComponent>();
    // iterate over each entity in the view
    polygons.each([&](const auto& body) {
        b2Vec2 position = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);       
    });

    // retrieve a view of entities with the BodyCircleComponent
    auto circles = registry.view<BodyCircleComponent>();
    // iterate over each entity in the view
    circles.each([&](const auto& body) {
        b2Vec2 position = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);       
    });
}