// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_player.h
//  header: component to designate the player entity in EnTT
// -----------------------------------------------------------------------------
#ifndef COMPONENT_PLAYER_H
#define COMPONENT_PLAYER_H

/** 
 * \brief   The PlayerComponent struct.
 * \details A struct only made for identifying the player entity when navigating
 *          the EnTT registry.
 */
struct PlayerComponent {
    /**
     * \brief Player ID, only used for identifying the player entity.
     */
    int m_id = 0;
};

#endif // COMPONENT_PLAYER_H
