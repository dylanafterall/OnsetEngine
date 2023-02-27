// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_collision.h
//  header: system to control game object collision
// -----------------------------------------------------------------------------

#include "system_collision.h"

void CollisionSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void CollisionSystem::BeginContact(b2Contact* contact) {
    auto a = contact->GetFixtureA()->GetUserData();
    auto b = contact->GetFixtureB()->GetUserData();
    FixtureUserDataComponent* aUserData = (FixtureUserDataComponent*)a.pointer;
    FixtureUserDataComponent* bUserData = (FixtureUserDataComponent*)b.pointer;

    if (aUserData && bUserData) {
        auto aEntity = *(*aUserData).m_enttEntity;
        auto bEntity = *(*bUserData).m_enttEntity;
        auto &aRenderable = (*m_registry).get<RenderDataComponent>(aEntity);
        auto &bRenderable = (*m_registry).get<RenderDataComponent>(bEntity);

        // if: a is player, b is sphere
        if ((*aUserData).m_fixtureType == 2 && (*bUserData).m_fixtureType == 3) {
            if (aRenderable.m_stencilFlag) {
                bRenderable.m_stencilFlag = !bRenderable.m_stencilFlag;
            }         
        }
        // else if: a is sphere, b is player
        else if ((*aUserData).m_fixtureType == 3 && (*bUserData).m_fixtureType == 2) {
            if (bRenderable.m_stencilFlag) {
                aRenderable.m_stencilFlag = !aRenderable.m_stencilFlag;
            }    
        }
    }
}

void CollisionSystem::EndContact(b2Contact* contact) {
}

void CollisionSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void CollisionSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}