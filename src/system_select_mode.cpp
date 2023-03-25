// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_select_mode.cpp
//  implementation: system to handle functionality needed for game's 'select mode'
// -----------------------------------------------------------------------------

#include "system_select_mode.h"

void SelectModeSystem::setRegistry(entt::registry* registry) {
    m_registry = registry;
}

void SelectModeSystem::moveSelectedLeft() {
    // get views of player and of selected objects
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent,
        RenderDataComponent
    >();
    auto selectables = (*m_registry).view<
        BodyTransformComponent,
        FixtureUserDataComponent,
        RenderDataComponent
    >();

    // move the player, then selectables if select mode is on
    bool selectModeOn;
    player.each([&](
        const auto& player,
        auto& body,
        const auto& renderData
    ) {
        selectModeOn = renderData.m_stencilFlag;
        b2Vec2 force = b2Vec2(-500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });

    if (selectModeOn) {
        selectables.each([&](
            auto& body,
            const auto& userData,
            const auto& renderData
        ) {
            if (userData.m_fixtureType == 3 && renderData.m_stencilFlag) {
                b2Vec2 force = b2Vec2(-500.0f, 0.0f);
                body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
            }
        });
    }
}

void SelectModeSystem::moveSelectedRight() {
    // get views of player and of selected objects
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent,
        RenderDataComponent
    >();
    auto selectables = (*m_registry).view<
        BodyTransformComponent,
        FixtureUserDataComponent,
        RenderDataComponent
    >();

    // move the player, then selectables if select mode is on
    bool selectModeOn;
    player.each([&](
        const auto& player,
        auto& body,
        const auto& renderData
    ) {
        selectModeOn = renderData.m_stencilFlag;
        b2Vec2 force = b2Vec2(500.0f, 0.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });

    if (selectModeOn) {
        selectables.each([&](
            auto& body,
            const auto& userData,
            const auto& renderData
        ) {
            if (userData.m_fixtureType == 3 && renderData.m_stencilFlag) {
                b2Vec2 force = b2Vec2(500.0f, 0.0f);
                body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
            }
        });
    }
}

void SelectModeSystem::moveSelectedUp() {
    // get views of player and of selected objects
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent,
        RenderDataComponent
    >();
    auto selectables = (*m_registry).view<
        BodyTransformComponent,
        FixtureUserDataComponent,
        RenderDataComponent
    >();

    // move the player, then selectables if select mode is on
    bool selectModeOn;
    player.each([&](
        const auto& player,
        auto& body,
        const auto& renderData
    ) {
        selectModeOn = renderData.m_stencilFlag;
        b2Vec2 force = b2Vec2(0.0f, 2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });

    if (selectModeOn) {
        selectables.each([&](
            auto& body,
            const auto& userData,
            const auto& renderData
        ) {
            if (userData.m_fixtureType == 3 && renderData.m_stencilFlag) {
                b2Vec2 force = b2Vec2(0.0f, 2000.0f);
                body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
            }
        });
    }
}

void SelectModeSystem::moveSelectedDown() {
    // get views of player and of selected objects
    auto player = (*m_registry).view<
        PlayerComponent,
        BodyTransformComponent,
        RenderDataComponent
    >();
    auto selectables = (*m_registry).view<
        BodyTransformComponent,
        FixtureUserDataComponent,
        RenderDataComponent
    >();

    // move the player, then selectables if select mode is on
    bool selectModeOn;
    player.each([&](
        const auto& player,
        auto& body,
        const auto& renderData
    ) {
        selectModeOn = renderData.m_stencilFlag;
        b2Vec2 force = b2Vec2(0.0f, -2000.0f);
        body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
    });

    if (selectModeOn) {
        selectables.each([&](
            auto& body,
            const auto& userData,
            const auto& renderData
        ) {
            if (userData.m_fixtureType == 3 && renderData.m_stencilFlag) {
                b2Vec2 force = b2Vec2(0.0f, -2000.0f);
                body.m_body->ApplyForce(force, body.m_body->GetPosition(), true);
            }
        });
    }
}

void SelectModeSystem::toggleSelectMode() {
    auto player = (*m_registry).view<
        PlayerComponent,
        RenderDataComponent
    >();
    auto stencils = (*m_registry).view<
        FixtureUserDataComponent,
        RenderDataComponent
    >();

    player.each([&](
        const auto& player,
        auto& renderData
    ) {
        // flip boolean value of stencilFlag: if true make false (& vice-versa)
        renderData.m_stencilFlag = !renderData.m_stencilFlag;

        // if we just turned off select mode, turn off all selected spheres
        if (renderData.m_stencilFlag == false) {
            stencils.each([&](
                const auto& userData,
                auto& renderData
            ) {
                if (userData.m_fixtureType == 3) {
                    renderData.m_stencilFlag = false;
                }
            });
        }
    });
}