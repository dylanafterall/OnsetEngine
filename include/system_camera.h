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
#include "component_body_transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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
     * \brief   Set EnTT registry within CameraSystem to accesss game data.
     */
    void setRegistry(entt::registry*);

    /**
     * \brief   This function translates, rotates, and zooms the game's main 
     *          camera entity.
     * \param   timeStep    The amount of time to simulate (representing seconds).
     * \param   registry    The game's EnTT registry for accessing camera entities.
     * \return  void, none.
     */
    void update(const float);

    /**
     * \brief   Translates the game's camera entity left in game space.
     */
    void translateCameraLeft();
    /**
     * \brief   Translates the game's camera entity right in game space.
     */
    void translateCameraRight();
    /**
     * \brief   Translates the game's camera entity up in game space.
     */
    void translateCameraUp();
    /**
     * \brief   Translates the game's camera entity down in game space.
     */
    void translateCameraDown();
    /**
     * \brief   Translates the game's camera entity forward in game space.
     */
    void translateCameraForward();
    /**
     * \brief   Translates the game's camera entity backward in game space.
     */
    void translateCameraBackward();

    /**
     * \brief   Zooms the game's camera entity into game space.
     */
    void zoomCameraIn();
    /**
     * \brief   Zooms the game's camera entity out of game space.
     */
    void zoomCameraOut();

    /**
     * \brief   Rotates the game's camera entity up in game space.
     */
    void pitchCameraUp();
    /**
     * \brief   Rotates the game's camera entity down in game space.
     */
    void pitchCameraDown();

    /**
     * \brief   Rotates the game's camera entity left in game space.
     */
    void yawCameraLeft();
    /**
     * \brief   Rotates the game's camera entity right in game space.
     */
    void yawCameraRight();

    /**
     * \brief   This function updates the member vectors of camera entities 
     *          (m_front, m_up, and m_right).
     * \param   registry    The game's EnTT registry for accessing camera entities.
     * \return  void, none.
     */
    void updateCameraVectors();

private:
    entt::registry* m_registry;

};

#endif // SYSTEM_CAMERA_H