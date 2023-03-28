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

#include "core_window_manager.h"
#include "core_asset_manager.h"
#include "core_audio_manager.h"
#include "core_input_invoker.h"
#include "core_log_manager.h"
#include "core_log_macros.h"
#include "core_text_manager.h"

#include "component_all.h"
#include "event_all.h"
#include "system_all.h"
#include "events/event_all.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

#include <memory>

/** 
 * \brief   The Game class.
 * \details Used by main() to manage all game properties. Initializes all 
 *          required subsystems. Generates graphic output. Handles input. 
 *          Updates game state. Begins and ends game loop.
 */
class Game {
public:
    /**
     * \brief   The default constructor. 
     */
    Game() = default;

    /**
     * \brief   The default destructor. 
     */
    ~Game() = default;

    /**
     * \brief   The function initialize. 
     * \details This function creates the game's Window and InputInvoker class 
     *          objects. It first sets up the invoker object, before then
     *          passing a pointer of the invoker to the window. Finally, 
     *          it initializes the window object - creating graphical output.
     * \return  void, none.
     */
    void initialize();

    /**
     * \brief   The function setup.
     * \details This function loads assets via the AssetManager class and 
     *          creates/registers entities.
     *          for a given game level. 
     * \return  void, none.
     */
    void setup();

    /**
     * \brief   The function run. 
     * \details This function contains the engine's game loop, which is 
     *          divided into 3 parts: processInput, update, and render. It
     *          also calculates the deltaTime for use in determining the 
     *          number of calls to update per game loop iteration, and for 
     *          rendering interpolation.
     * \return  void, none.
     */
    void run();

    /**
     * \brief   The function processInput. 
     * \details This function handles input handling which affects the game
     *          loop. Examples include player, hardware, or network input.
     * \return  void, none.
     */
    void processInput();

    /**
     * \brief   The function update. 
     * \details This function calls on various 'system' classes to update their
     *          status, based on a constant timeStep (as opposed to a variable 
     *          deltaTime). This is to ensure physics and similar simulations 
     *          update in fixed, discrete sized steps. Results in deterministic
     *          behavior (decoupled from rendering).
     * \param   timeStep            The amount of time to simulate. Fixed
     *                                 value (representing seconds).
     * \param   velocityIterations  For Box2D's velocity constraint solver.
     * \param   positionIterations  For Box2D's position constraint solver. 
     * \return  void, none.
     */
    void update(const float, const int32, const int32);

    /**
     * \brief   The function render. 
     * \details This function calls on OpenGL to fill its back buffer, then
     *          calls the RenderSystem class to draw EnTT entities on the back
     *          buffer, then swaps front and back buffers. 
     * \param   renderFactor  For render interpolation (lag / timeStep).
     * \return  void, none.
     */
    void render(const float);

    /**
     * \brief   The function destroy. 
     * \details This function ensures that all heap memory allocated for the
     *          Game class is de-allocated.
     * \return  void, none.
     */
    void destroy();

private:
    /**
     * \brief Variable used to break the game loop.
     */
    bool m_isRunning = false;

    /**
     * \brief Variable used to change game's aspect ratio.
     */
    unsigned int m_screenWidth = 800;
    /**
     * \brief Variable used to change game's aspect ratio.
     */
    unsigned int m_screenHeight = 600;
    /**
     * \brief Variable used to change shadow map resolution.
     */
    unsigned int m_shadowWidth = 1024;
    /**
     * \brief Variable used to change shadow map resolution.
     */
    unsigned int m_shadowHeight = 1024;


    /**
     * \brief Variable used in calculating game's deltaTime and lag.
     */
    double previousTime = 0.0;
    /**
     * \brief Variable used to calculate number of update steps and render
     *        interpolation.
     */
    double lag = 0.0;

    /**
     * \brief Object to manage the game's window using OpenGL API.
     */
    std::unique_ptr<WindowManager> m_windowManager;
    /**
     * \brief Object that acts as a layer of abstraction between callback 
     *        functions and associated game commands.
     */
    std::unique_ptr<InputInvoker> m_inputInvoker;
    /**
     * \brief Object used to import mesh, shader, texture, and audio assets.
     */
    AssetManager m_assetManager;
    /**
     * \brief Object to act as a wrapper class around spdlog functionality.
     */
    LogManager m_logManager;
    /**
     * \brief Object to manage the game's renderable text characters.
     */
    TextManager m_textManager;
    /**
     * \brief Object to manage the game's sound/audio functionality.
     */
    AudioManager m_audioManager;

    /**
     * \brief Object to translate/rotate the camera.
     */
    CameraSystem m_cameraSystem;
    /**
     * \brief Object to handle Box2D object collisions.
     */
    CollisionSystem m_collisionSystem;
    /**
     * \brief Object to render entities of game's registry.
     */
    RenderSystem m_renderSystem;
    /**
     * \brief Object to play sound buffers of game entities.
     */
    AudioSystem m_audioSystem;
    /**
     * \brief Object to control player movement functionality.
     */
    PlayerMovementSystem m_playerMovementSystem;
    /**
     * \brief Object to control 'select mode' functionality.
     */
    SelectModeSystem m_selectModeSystem;

    /**
     * \brief EnTT registry to manage all game entities.
     */
    entt::registry m_registry;
    /**
     * \brief EnTT default event dispatcher.
     */
    entt::dispatcher m_dispatcher;

    /**
     * \brief Fixed time step for simulation (0.1 secs default).
     */
    const float TIME_STEP = 0.01f;
    /**
     * \brief Box2D constraint solver, 8 recommended by Box2D documentation.
     */
    const int32 VELOCITY_ITERATIONS = 8;
    /**
     * \brief Box2D constraint solver, 3 recommended by Box2D documentation.
     */
    const int32 POSITION_ITERATIONS = 3;
    /**
     * \brief Object used by Box2D to simulate game-world gravity.
     */
    std::unique_ptr<b2Vec2> m_gravity = std::make_unique<b2Vec2>(0.0f, -10.0f);
    /**
     * \brief Object used by Box2D to manage physics bodies in game-world.
     */
    std::unique_ptr<b2World> m_world = std::make_unique<b2World>(*m_gravity);
};

#endif // CORE_GAME_H
