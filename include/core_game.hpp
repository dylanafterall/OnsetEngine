// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.hpp
//  header of Game class, controls game loop  
// -----------------------------------------------------------------------------
#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "core_asset_manager.hpp"
#include "core_window.hpp"
#include "system_all.hpp"

#include "GLFW/glfw3.h"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

#include <memory>

class Game {
public:
    // constructor and destructor
    Game();
    ~Game();

    // pre loop
    void initialize();
    void setup();

    // game loop
    void run();
    void processInput();
    void update(const float, const int32, const int32);
    void render(float);

    // post loop
    void destroy();

private:
    unsigned int m_screenWidth = 800;
    unsigned int m_screenHeight = 600;
    Window* m_windowPtr;
    InputInvoker* m_invokerPtr;
    // timestep variables (specifically) for rendering
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
    // core classes
    AssetManager m_assetManager;
    // system classes
    RenderSystem m_renderSystem;
    MovementSystem m_movementSystem;
    CameraSystem m_cameraSystem;
};

#endif // CORE_GAME_HPP
