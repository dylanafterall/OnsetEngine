// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_collision.h
//  header: system to control game object collision
// -----------------------------------------------------------------------------
#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include "component_fixture_user_data.h"
#include "component_render_data.h"

#include "entt/entt.hpp"
#include "box2d/box2d.h"

class CollisionSystem : public b2ContactListener {
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void setRegistry(entt::registry*);

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:
    entt::registry* m_registry;
};

#endif // SYSTEM_COLLISION_H