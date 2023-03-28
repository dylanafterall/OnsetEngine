// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_audio_manager.h
//  header of AudioManager class, for use of OpenAL sound functionality
// -----------------------------------------------------------------------------
#ifndef CORE_AUDIO_MANAGER_H
#define CORE_AUDIO_MANAGER_H

#include "core_log_macros.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "sndfile.h"

#include <inttypes.h>
#include <map>
#include <string>

/** 
 * \brief   The AudioManager class.
 * \details Used by Game class to setup and use OpenAL library for sound affect
 *          and music functionality.
 */
class AudioManager {
public:
    /**
     * \brief   The default constructor. 
     */
    AudioManager();
    /**
     * \brief   The default destructor. 
     */
    ~AudioManager();

    /**
     * \brief   The function setSoundEffect(). 
     * \details This function adds a sound effect from the Assets directory and 
     *          stores it as ALuint ID within a private vector for use in game 
     *          components.
     * \param   assetID     Name/unique string of sound effect to use as key in map.
     * \param   filename    Name of file in system containing sound effect to import.
     * \return  void, none.
     */
    void setSoundEffect(const std::string&, const char*);

    /**
     * \brief   The function getSoundEffect. 
     * \details This function, given a key for std::map m_soundEffectBuffers, 
     *          returns the associated ALuint from OpenAL.
     * \param   program      The name of the key to search the m_soundEffectBuffers
     *                       map for.
     * \retval  assetID      An ALuint stored by OpenAL for an associated sound 
     *                       effect buffer.
     */
    ALuint getSoundEffect(const std::string&);

    /**
     * \brief   The function deleteBuffers(). 
     * \details This function removes all sound effects - deallocating memory
     *          allocated by OpenAL, and removing all sound effect buffers 
     *          from the buffer vector in AudioManager.
     * \return  none, void.
     */
    void deleteBuffers();

private:
    /**
     * \brief Pointer to OpenAL sound device.
     */
    ALCdevice* p_ALCDevice;
    /**
     * \brief Pointer to current OpenAL context.
     */
	ALCcontext* p_ALCContext;

    /**
     * \brief std::map used to store sound buffer IDs for easy lookup when 
     *        creating new game entities.
     */
    std::map<std::string, ALuint> m_soundEffectBuffers;
};

#endif // CORE_AUDIO_MANAGER_H