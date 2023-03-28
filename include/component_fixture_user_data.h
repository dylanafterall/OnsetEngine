// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_fixture_user_data.h
//  header: component to hold user data for Box2D
// -----------------------------------------------------------------------------
#ifndef COMPONENT_FIXTURE_USER_DATA_H
#define COMPONENT_FIXTURE_USER_DATA_H

#include "box2d/box2d.h"
#include "entt/entt.hpp"

/** 
 * \brief   The FixtureUserDataComponent struct.
 * \details A struct to hold user data used to connect Box2D fixtures to 
 *          associated game actors/objects/entities. Can add a category for any
 *          game entity information relevant to Box2D.
 */
struct FixtureUserDataComponent {
    /**
     * \brief Integer representing what type of game object is associated with
     *          a given Box2D fixture.
     *          0: camera
     *          1: light
     *          2: player
     *          3: spheres (able to be 'selected')
     *          4: non-spheres
     */
    int m_fixtureType;
    /**
     * \brief Pointer to memory address for EnTT::entity associated with this fixture.
     */
    entt::entity* m_enttEntity;
};

#endif // COMPONENT_FIXTURE_USER_DATA_H