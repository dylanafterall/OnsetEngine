// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.h
//  header of Game class, controls game loop  
// -----------------------------------------------------------------------------
#ifndef CORE_GAME_H
#define CORE_GAME_H

#define ONSET_CONFIG_DEBUG
#define ONSET_PLATFORM_MAC

#include "component_all.h"
#include "core_asset_manager.h"
#include "core_window.h"
#include "core_log_manager.h"
#include "core_log_macros.h"
#include "system_all.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

#include <memory>

class Game {
public:
    // constructor and destructor
    Game();
    ~Game();

    // pre loop
    void getInfo();
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
    bool m_isRunning;
    unsigned int m_screenWidth = 800;
    unsigned int m_screenHeight = 600;
     // rendering deltatime
    double previousTime = 0.0;
    double lag = 0.0;
    // core classes
    Window* m_windowPtr;
    InputInvoker* m_invokerPtr;
    AssetManager m_assetManager;
    LogManager m_logManager;
    // system classes
    RenderSystem m_renderSystem;
    CameraSystem m_cameraSystem;

    // EnTT 
    entt::registry m_registry;
    // Box2D physics
    const float TIME_STEP = 0.01f;
    const int32 VELOCITY_ITERATIONS = 8;    // 8 is recommended by Box2D
    const int32 POSITION_ITERATIONS = 3;    // 3 is recommended by Box2D
    std::unique_ptr<b2Vec2> m_gravity = std::make_unique<b2Vec2>(0.0f, -10.0f);
    std::unique_ptr<b2World> m_world = std::make_unique<b2World>(*m_gravity);
};

#endif // CORE_GAME_H
