// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_audio.cpp
//  implementation: Audio System to play sound effect buffers via OpenAL
// -----------------------------------------------------------------------------

#include "system_audio.h"


void AudioSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void AudioSystem::deleteSources() {
    auto soundSource = (*m_registry).view<
        AudioDataComponent
    >();
    soundSource.each([&](
        auto& audio
    ) {
        alDeleteSources(1, &audio.m_soundSource);
    });
}

void AudioSystem::playSelectModeToggleSound() {
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent,
        AudioDataComponent,
        RenderDataComponent
    >();
    player.each([&](
        const auto& player,
        const auto& body,
        const auto& audio,
        const auto& graphics
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        b2Vec2 velocity = body.m_body->GetLinearVelocity();

        // if select mode was just toggled on (and thus true)
        if (graphics.m_stencilFlag) {
            alSourcef(audio.m_soundSource, AL_PITCH, audio.m_selectModeOnSound.m_pitch);
            alSourcef(audio.m_soundSource, AL_GAIN, audio.m_selectModeOnSound.m_gain);
            alSource3f(audio.m_soundSource, AL_POSITION, position.x, position.y, 0.0f);
            alSource3f(audio.m_soundSource, AL_VELOCITY, velocity.x, velocity.y, 0.0f);
            alSourcei(audio.m_soundSource, AL_LOOPING, audio.m_selectModeOnSound.m_loop);
            alSourcei(audio.m_soundSource, AL_BUFFER, audio.m_selectModeOnSound.m_soundBuffer);
        }
        // if select mode was just toggled off (and thus false)
        else {
            alSourcef(audio.m_soundSource, AL_PITCH, audio.m_selectModeOffSound.m_pitch);
            alSourcef(audio.m_soundSource, AL_GAIN, audio.m_selectModeOffSound.m_gain);
            alSource3f(audio.m_soundSource, AL_POSITION, position.x, position.y, 0.0f);
            alSource3f(audio.m_soundSource, AL_VELOCITY, velocity.x, velocity.y, 0.0f);
            alSourcei(audio.m_soundSource, AL_LOOPING, audio.m_selectModeOffSound.m_loop);
            alSourcei(audio.m_soundSource, AL_BUFFER, audio.m_selectModeOffSound.m_soundBuffer);
        }

        alSourcePlay(audio.m_soundSource);
    });
}