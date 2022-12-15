// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_collision.h
//  header: system to control game object collision
// -----------------------------------------------------------------------------

#include "system_collision.h"

void CollisionSystem::BeginContact(b2Contact* contact) {
    std::cout << "CollisionSystem::BeginContact" << std::endl;
}

void CollisionSystem::EndContact(b2Contact* contact) {
    std::cout << "CollisionSystem::EndContact" << std::endl;
}

void CollisionSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    // std::cout << "CollisionSystem::PreSolve" << std::endl;
}

void CollisionSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    // std::cout << "CollisionSystem::PostSolve" << std::endl;
}