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
    void update(const double stepTime);
    void render(double renderFactor);

    // Post - Game Loop
    void destroy();

private:
    // Timestep variables 
    double previousTime = 0.0;
    double lag = 0.0;
    const double STEP_TIME = 0.01;

    // ProcessInput variables
    bool keys[1024];
    bool keysProcessed[1024];

    Window m_window;

    AssetManager m_assetManager;

    entt::registry m_registry;
};

#endif // CORE_GAME_HPP
