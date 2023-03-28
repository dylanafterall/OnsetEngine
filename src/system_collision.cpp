// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_collision.h
//  header: system to control game object collision
// -----------------------------------------------------------------------------

#include "system_collision.h"

void CollisionSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void CollisionSystem::setDispatcher(entt::dispatcher* dispatcher) {
    m_dispatcher = dispatcher;
}

void CollisionSystem::BeginContact(b2Contact* contact) {
    auto a = contact->GetFixtureA()->GetUserData();
    auto b = contact->GetFixtureB()->GetUserData();
    FixtureUserDataComponent* aUserData = (FixtureUserDataComponent*)a.pointer;
    FixtureUserDataComponent* bUserData = (FixtureUserDataComponent*)b.pointer;

    if (aUserData && bUserData) {
        auto aEntity = *(*aUserData).m_enttEntity;
        auto bEntity = *(*bUserData).m_enttEntity;
        auto &aRenderable = (*m_registry).get<RenderDataComponent>(aEntity);
        auto &bRenderable = (*m_registry).get<RenderDataComponent>(bEntity);

        // if: a is player, b is sphere
        if ((*aUserData).m_fixtureType == 2 && (*bUserData).m_fixtureType == 3) {
            // if: player is in select mode
            if (aRenderable.m_stencilFlag) {
                // flip other sphere's select-mode status
                bRenderable.m_stencilFlag = !bRenderable.m_stencilFlag;
            }   
            // play the sphere's collision sound
            auto &bBody = (*m_registry).get<BodyTransformComponent>(bEntity);
            b2Vec2 position = bBody.m_body->GetPosition();
            b2Vec2 velocity = bBody.m_body->GetLinearVelocity();
            auto &bAudio = (*m_registry).get<AudioDataComponent>(bEntity);
            alSourcef(bAudio.m_soundSource, AL_PITCH, bAudio.m_collisionSound.m_pitch);
            alSourcef(bAudio.m_soundSource, AL_GAIN, bAudio.m_collisionSound.m_gain);
            alSource3f(bAudio.m_soundSource, AL_POSITION, position.x, position.y, 0.0f);
            alSource3f(bAudio.m_soundSource, AL_VELOCITY, velocity.x, velocity.y, 0.0f);
            alSourcei(bAudio.m_soundSource, AL_LOOPING, bAudio.m_collisionSound.m_loop);
            alSourcei(bAudio.m_soundSource, AL_BUFFER, bAudio.m_collisionSound.m_soundBuffer);
            alSourcePlay(bAudio.m_soundSource);
        }
        // else if: a is sphere, b is player
        else if ((*aUserData).m_fixtureType == 3 && (*bUserData).m_fixtureType == 2) {
            // if: player is in select mode
            if (bRenderable.m_stencilFlag) {
                // flip other sphere's select-mode status
                aRenderable.m_stencilFlag = !aRenderable.m_stencilFlag;
            }   
            // play the sphere's collision sound
            auto &aBody = (*m_registry).get<BodyTransformComponent>(aEntity);
            b2Vec2 position = aBody.m_body->GetPosition();
            b2Vec2 velocity = aBody.m_body->GetLinearVelocity();
            auto &aAudio = (*m_registry).get<AudioDataComponent>(aEntity);
            alSourcef(aAudio.m_soundSource, AL_PITCH, aAudio.m_collisionSound.m_pitch);
            alSourcef(aAudio.m_soundSource, AL_GAIN, aAudio.m_collisionSound.m_gain);
            alSource3f(aAudio.m_soundSource, AL_POSITION, position.x, position.y, 0.0f);
            alSource3f(aAudio.m_soundSource, AL_VELOCITY, velocity.x, velocity.y, 0.0f);
            alSourcei(aAudio.m_soundSource, AL_LOOPING, aAudio.m_collisionSound.m_loop);
            alSourcei(aAudio.m_soundSource, AL_BUFFER, aAudio.m_collisionSound.m_soundBuffer); 
            alSourcePlay(aAudio.m_soundSource);
        }
        // else if collision is not between player and a sphere
        else {
            // play first object's sound
            auto &aBody = (*m_registry).get<BodyTransformComponent>(aEntity);
            b2Vec2 aPosition = aBody.m_body->GetPosition();
            b2Vec2 aVelocity = aBody.m_body->GetLinearVelocity();
            auto &aAudio = (*m_registry).get<AudioDataComponent>(aEntity);
            alSourcef(aAudio.m_soundSource, AL_PITCH, aAudio.m_collisionSound.m_pitch);
            alSourcef(aAudio.m_soundSource, AL_GAIN, aAudio.m_collisionSound.m_gain);
            alSource3f(aAudio.m_soundSource, AL_POSITION, aPosition.x, aPosition.y, 0.0f);
            alSource3f(aAudio.m_soundSource, AL_VELOCITY, aVelocity.x, aVelocity.y, 0.0f);
            alSourcei(aAudio.m_soundSource, AL_LOOPING, aAudio.m_collisionSound.m_loop);
            alSourcei(aAudio.m_soundSource, AL_BUFFER, aAudio.m_collisionSound.m_soundBuffer); 
            alSourcePlay(aAudio.m_soundSource);
            // play second object's sound
            auto &bBody = (*m_registry).get<BodyTransformComponent>(bEntity);
            b2Vec2 bPosition = bBody.m_body->GetPosition();
            b2Vec2 bVelocity = bBody.m_body->GetLinearVelocity();
            auto &bAudio = (*m_registry).get<AudioDataComponent>(bEntity);
            alSourcef(bAudio.m_soundSource, AL_PITCH, bAudio.m_collisionSound.m_pitch);
            alSourcef(bAudio.m_soundSource, AL_GAIN, bAudio.m_collisionSound.m_gain);
            alSource3f(bAudio.m_soundSource, AL_POSITION, bPosition.x, bPosition.y, 0.0f);
            alSource3f(bAudio.m_soundSource, AL_VELOCITY, bVelocity.x, bVelocity.y, 0.0f);
            alSourcei(bAudio.m_soundSource, AL_LOOPING, bAudio.m_collisionSound.m_loop);
            alSourcei(bAudio.m_soundSource, AL_BUFFER, bAudio.m_collisionSound.m_soundBuffer); 
            alSourcePlay(bAudio.m_soundSource);
        }
    }
}

void CollisionSystem::EndContact(b2Contact* contact) {
}

void CollisionSystem::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void CollisionSystem::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}