// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_player_movement.h
//  header: system to move the 'player' entity in game space
// -----------------------------------------------------------------------------
#ifndef SYSTEM_PLAYER_MOVEMENT_H
#define SYSTEM_PLAYER_MOVEMENT_H

#include "component_player.h"
#include "component_body_transform.h"

#include "entt/entt.hpp"
#include "box2d/box2d.h"

class PlayerMovementSystem {
public:
    /**
     * \brief   The default constructor. 
     */
    PlayerMovementSystem() = default;
    /**
     * \brief   The default destructor. 
     */
    ~PlayerMovementSystem() = default;

    /**
     * \brief   Set EnTT registry within PlayerMovement to accesss game data.
     */
    void setRegistry(entt::registry*);

    /**
     * \brief   Apply a force to game's player entity towards left direction.
     */
    void movePlayerLeft();
    /**
     * \brief   Apply a force to game's player entity towards right direction.
     */
    void movePlayerRight();
    /**
     * \brief   Apply a force to game's player entity towards up direction.
     */
    void movePlayerUp();
    /**
     * \brief   Apply a force to game's player entity towards down direction.
     */
    void movePlayerDown();

private:
    entt::registry* m_registry;
};


#endif // SYSTEM_PLAYER_MOVEMENT_H