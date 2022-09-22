// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.cpp
//  implementation of Game class, controls game loop  
// -----------------------------------------------------------------------------
// TODO: allow user to change refresh rate and monitor
//          add ability to change framerate? 
//          interpolate rendering based on renderFactor

#include "core_game.hpp"
#include "component_texture.hpp"
#include "component_shader.hpp"
#include "component_shaderprogram.hpp"
#include "component_boxbody.hpp"

#include "system_movement.hpp"
#include "system_render.hpp"

#include "spdlog/spdlog.h"
#include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/type_ptr.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Constructor and Destructor

Game::Game() {
    spdlog::info("Game Constructor called!");
}

Game::~Game() {
    spdlog::info("Game Destructor called!");
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Pre - Game Loop

void Game::initialize() {
    // initialize GLFW window and GLAD
    m_window.initialize();

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);    // used for z-buffer 
}

void Game::setup() {
    // AssetManager ............................................................
    m_assetManager.setVShader("vert", "../asset/shader/v.vert");
    m_assetManager.setFShader("frag", "../asset/shader/f.frag");
    m_assetManager.setTexture("container", "../asset/texture/container.jpg");
    m_assetManager.setTexture("awesomeface", "../asset/texture/awesomeface.png");    

    unsigned int vertex = m_assetManager.getVShader("vert");
    unsigned int fragment = m_assetManager.getFShader("frag");
    m_assetManager.setShaderProgram("vert&frag", vertex, fragment);

    // Box2D ...................................................................
    // make bottom static box
    BoxBodyComponent bottomBox;
    bottomBox.m_bodyDef.position.Set(0.0f, -10.0f);
    bottomBox.m_body = m_world->CreateBody(&bottomBox.m_bodyDef);
    bottomBox.m_polygonShape.SetAsBox(50.0f, 10.0f);
    bottomBox.m_body->CreateFixture(&bottomBox.m_polygonShape, 0.0f);

    // make top dynamic box
    BoxBodyComponent topBox;
    topBox.m_bodyDef.type = b2_dynamicBody;
    topBox.m_bodyDef.position.Set(0.0f, 4.0f);
    topBox.m_body = m_world->CreateBody(&topBox.m_bodyDef);
    topBox.m_polygonShape.SetAsBox(1.0f, 1.0f);
    topBox.m_fixtureDef.shape = &topBox.m_polygonShape;
    topBox.m_fixtureDef.density = 1.0f;
    topBox.m_fixtureDef.friction = 0.3f;
    topBox.m_body->CreateFixture(&topBox.m_fixtureDef);

    // EnTT ....................................................................
    auto player = m_registry.create();
    m_registry.emplace<TextureComponent>(player, m_assetManager.getTexture("container"));
    m_registry.emplace<ShaderProgramComponent>(player, m_assetManager.getShaderProgram("vert&frag"));

    auto lowerBox = m_registry.create();
    m_registry.emplace<BoxBodyComponent>(lowerBox, bottomBox);
    auto upperBox = m_registry.create();
    m_registry.emplace<BoxBodyComponent>(upperBox, topBox);

}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Game Loop

void Game::run() {
    // glfwWindowShouldClose() returns GL_FALSE until window instructed to close
    while (!glfwWindowShouldClose(m_window.m_glfwWindow)) {
        // find time-step ...................................................... 
        double currentTime = glfwGetTime();    // returns time in secs
        double deltaTime = currentTime - previousTime;
        // cap the max number of Update() looping - to prevent locking up
        if (deltaTime > 0.25) {
            deltaTime = 0.25;   // max of 25 loops, since SECS_PER_UPDATE = 0.01 
            spdlog::warn("The calculated deltaTime exceeded 0.25 seconds");
        }
        previousTime = currentTime;
        lag += deltaTime;

        // game loop ...........................................................
        processInput();
        // use a fixed-step for Update(), for physics and AI
        while (lag >= TIME_STEP) {
            update(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
            lag -= TIME_STEP;
        }
        // normalize renderFactor [0, 1.0], used  to interpolate rendering
        render(lag / TIME_STEP); 
    }
}

void Game::processInput() {
    // query GLFW whether relevant keys pressed/released this frame 
    // close the window if player presses escape key
    if (glfwGetKey(m_window.m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window.m_glfwWindow, true);
    }
}

void Game::update(const float timeStep, const int32 velocityIterations, const int32 positionIterations) {
    // call window and input callbacks associated with these events
    glfwPollEvents();

    // Box2D simulation
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_movementSystem.update(timeStep, m_registry);
}

void Game::render(double renderFactor) {
    // specify color values to then use in filling color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // R, G, B, Alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    m_renderSystem.update()
    */

    // swap front and back buffers (drawing to back buffer, displaying front)
    glfwSwapBuffers(m_window.m_glfwWindow);
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Post - Game Loop

void Game::destroy() {
    // de-allocate GL shader program and array, buffer, and element objects
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}
