// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// event_player_collision.h
//  header: event of player colliding with another mesh object
// -----------------------------------------------------------------------------
#ifndef EVENT_PLAYER_COLLISION_H
#define EVENT_PLAYER_COLLISION_H

struct PlayerCollisionEvent final {
    /**
     * \brief   The default constructor. 
     */
    PlayerCollisionEvent() = default;
    /**
     * \brief   The default destructor. 
     */
    ~PlayerCollisionEvent() = default;

    bool m_playerCollided = false;
};

#endif // EVENT_PLAYER_COLLISION_H