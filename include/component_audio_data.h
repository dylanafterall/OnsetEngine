// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// component_audio_data.h
//  header: component to hold audio data (sound buffer ID) for OpenAL
// -----------------------------------------------------------------------------
#ifndef COMPONENT_AUDIO_DATA_H
#define COMPONENT_AUDIO_DATA_H

#include "AL/al.h"
#include "entt/entt.hpp"

struct BufferData {
    ALuint m_soundBuffer;
    float m_pitch;
    float m_gain;
    bool m_loop;
};

/** 
 * \brief   The AudioDataComponent struct.
 * \details A struct to hold data pertaining to OpenAL sound buffers. Passed into 
 *          AudioSystem via EnTT registry for playing sound effects.
 */
struct AudioDataComponent {
    /**
     * \brief Unique OpenAL ID for a sound source.
     */
    ALuint m_soundSource;

    /**
     * \brief Unique OpenAL ID for a sound buffer object.
     */
    BufferData m_collisionSound;
    /**
     * \brief Unique OpenAL ID for a sound buffer object.
     */
    BufferData m_selectModeOnSound;
    /**
     * \brief Unique OpenAL ID for a sound buffer object.
     */
    BufferData m_selectModeOffSound;
};

#endif // COMPONENT_AUDIO_DATA_H