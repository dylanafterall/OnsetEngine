// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_audio.h
//  header: Audio System to play sound effect buffers via OpenAL
// -----------------------------------------------------------------------------
#ifndef SYSTEM_AUDIO_H
#define SYSTEM_AUDIO_H

#include "component_player.h"
#include "component_body_transform.h"
#include "component_audio_data.h"
#include "component_render_data.h"

#include "AL/al.h"
#include "box2d/box2d.h"
#include "entt/entt.hpp"

/** 
 * \brief   The AudioSystem class.
 * \details Used by Game class to play sound buffers via OpenAL.
 */
class AudioSystem {
public:
    /**
     * \brief   The default constructor. 
     */
    AudioSystem() = default;
    /**
     * \brief   The default destructor. 
     */
    ~AudioSystem() = default;

    /**
     * \brief   Deallocate memory reserved by OpenAL for sound sources. 
     */
    void deleteSources();
    /**
     * \brief   Set the EnTT registry in order to access entity data for 
     *          playing sounds. 
     */
    void setRegistry(entt::registry*);

    /**
     * \brief   Plays select-mode toggle sound effect via OpenAL.
     */
    void playSelectModeToggleSound();

private:
    entt::registry* m_registry;
};

#endif // SYSTEM_AUDIO_H