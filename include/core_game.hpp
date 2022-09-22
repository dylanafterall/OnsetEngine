// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.hpp
//  header of Game class, controls game loop  
// -----------------------------------------------------------------------------
#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "core_assetmanager.hpp"
#include "core_window.hpp"

#include "GLFW/glfw3.h"
#include "entt/entt.hpp"
#include "box2d/box2d.h"
#include "system_movement.hpp"
#include "system_render.hpp"

#include <memory>

class Game {
public:
    // Constructor and Destructor
    Game();
    ~Game();

    // Pre - Game Loop
    void initialize();
    void setup();

    // Game Loop
    void run();
    void processInput();
    void update(const float timeStep, const int32 velocityIterations, const int32 positionIterations);
    void render(double renderFactor);

    // Post - Game Loop
    void destroy();

private:
    // ProcessInput variables
    bool keys[1024];
    bool keysProcessed[1024];

    // Timestep variables (specifically) for rendering
    double previousTime = 0.0;
    double lag = 0.0;

    // Box2D physics variables
    const float TIME_STEP = 0.01f;
    const int32 VELOCITY_ITERATIONS = 8;    // 8 is recommended by Box2D
    const int32 POSITION_ITERATIONS = 3;    // 3 is recommended by Box2D
    std::unique_ptr<b2Vec2> m_gravity = std::make_unique<b2Vec2>(0.0f, -10.0f);
    std::unique_ptr<b2World> m_world = std::make_unique<b2World>(*m_gravity);

    // EnTT 
    entt::registry m_registry;

    // Core Classes
    Window m_window;
    AssetManager m_assetManager;

    // System Classes
    MovementSystem m_movementSystem;
    RenderSystem m_renderSystem;
};

#endif // CORE_GAME_HPP
