// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_camera.h
//  header: system to control camera movement
// -----------------------------------------------------------------------------
#ifndef SYSTEM_CAMERA_H
#define SYSTEM_CAMERA_H

#include "component_camera.h"
#include "component_player.h"
#include "component_body_circle.h"
#include "component_body_polygon.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

/** 
 * \brief   The CameraSystem class.
 * \details Used by Game class to update camera entity transforms (translation,
 *          rotation, zoom).
 */
class CameraSystem {
public:
    /**
     * \brief   The default constructor. 
     */
    CameraSystem() = default;
    /**
     * \brief   The default destructor. 
     */
    ~CameraSystem() = default;

    /**
     * \brief   The function update. 
     * \details This function translates, rotates, and zooms the game's main 
     *          camera entity.
     * \param   timeStep    The amount of time to simulate (representing seconds).
     * \param   registry    The game's EnTT registry for accessing camera entities.
     * \return  void, none.
     */
    void update(const float, entt::registry&);

private:
    /**
     * \brief   The function updateCameraVectors. 
     * \details This function updates the member vectors of camera entities 
     *          (m_front, m_up, and m_right).
     * \param   registry    The game's EnTT registry for accessing camera entities.
     * \return  void, none.
     */
    void updateCameraVectors(entt::registry&);

};

#endif // SYSTEM_CAMERA_H