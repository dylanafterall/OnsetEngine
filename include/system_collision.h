// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_collision.h
//  header: system to control game object collision
// -----------------------------------------------------------------------------
#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include "entt/entt.hpp"
#include "box2d/box2d.h"

#include <iostream>

class CollisionSystem : public b2ContactListener {
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // SYSTEM_COLLISION_H