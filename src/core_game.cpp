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

#include "core_game.h"
#include "component_shader.h"
#include "component_texture.h"

#include "spdlog/spdlog.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

    // configure global opengl state ...........................................
    glEnable(GL_DEPTH_TEST);    // used for z-buffer 
}

void Game::setup() {
    m_assetManager.setVShader("vert", "../asset/shader/v.vert");
    m_assetManager.setFShader("frag", "../asset/shader/f.frag");
    m_assetManager.setTexture("container", "../asset/texture/container.jpg");
    m_assetManager.setTexture("awesomeface", "../asset/texture/awesomeface.png");    

    unsigned int vertex = m_assetManager.getVShader("vert");
    unsigned int fragment = m_assetManager.getFShader("frag");

    // link shaders
    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // test if linking successful
    int success;
    char infoLog[1024];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (success) {
        spdlog::info("Linked shaders into shader program object");
    }
    else {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        spdlog::error(
            "Shader linking error of type: LINKER: {}",
            infoLog
        );
    }
    
    auto player = m_registry.create();
    // create, initialize, and assign to entity the given component
    m_registry.emplace<ShaderComponent>(player, m_assetManager.getVShader("vert"), m_assetManager.getFShader("frag"));
    m_registry.emplace<TextureComponent>(player, m_assetManager.getTexture("container"));
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
        while (lag >= STEP_TIME) {
            update(STEP_TIME);
            lag -= STEP_TIME;
        }
        // normalize renderFactor [0, 1.0], used  to interpolate rendering
        render(lag / STEP_TIME); 
    }
}

void Game::processInput() {
    // query GLFW whether relevant keys pressed/released this frame 
    // close the window if player presses escape key
    if (glfwGetKey(m_window.m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window.m_glfwWindow, true);
    }
}

void Game::update(const double stepTime) {
    // call window and input callbacks associated with these events
    glfwPollEvents();
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