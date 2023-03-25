// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_select_mode.h
//  header: system to handle functionality needed for game's 'select mode'
// -----------------------------------------------------------------------------
#ifndef SYSTEM_SELECT_MODE_H
#define SYSTEM_SELECT_MODE_H

#include "component_fixture_user_data.h"
#include "component_body_transform.h"
#include "component_player.h"
#include "component_render_data.h"

#include "entt/entt.hpp"
#include "box2d/box2d.h"

class SelectModeSystem {
public:
    /**
     * \brief   The default constructor. 
     */
    SelectModeSystem() = default;
    /**
     * \brief   The default destructor. 
     */
    ~SelectModeSystem() = default;

    /**
     * \brief   Set the EnTT registry to access game data inside SelectMode. 
     */
    void setRegistry(entt::registry*);

    /**
     * \brief   Apply force to player and selected objects in left direction.
     */
    void moveSelectedLeft();
    /**
     * \brief   Apply force to player and selected objects in right direction. 
     */
    void moveSelectedRight();
    /**
     * \brief   Apply force to player and selected objects in up direction.
     */
    void moveSelectedUp();
    /**
     * \brief   Apply force to player and selected objects in down direction. 
     */
    void moveSelectedDown();

    /**
     * \brief   Toggle select mode: on if currently off, off if currently on. 
     */
    void toggleSelectMode();

private:
    entt::registry* m_registry;

};

#endif // SYSTEM_SELECT_MODE_H