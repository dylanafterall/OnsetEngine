// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_player_movement.cpp
//  implementation: system to move the 'player' entity in game space
// -----------------------------------------------------------------------------

#include "system_player_movement.h"

void PlayerMovementSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void PlayerMovementSystem::movePlayerLeft() {
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent
    >();
    player.each([&](
        const auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(-500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void PlayerMovementSystem::movePlayerRight() {
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent
    >();
    player.each([&](
        const auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void PlayerMovementSystem::movePlayerUp() {
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent
    >();
    player.each([&](
        const auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(0.0f, 2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}

void PlayerMovementSystem::movePlayerDown() {
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent
    >();
    player.each([&](
        const auto& player,
        auto& body
    ) {
        b2Vec2 force = b2Vec2(0.0f, -2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });
}