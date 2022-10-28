// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.cpp
//  implementation of Game class, controls game loop  
// -----------------------------------------------------------------------------

#include "core_game.hpp"
#include "GLFW/glfw3.h"
#include "component_all.hpp"

#include "spdlog/spdlog.h"
#include "glm/glm.hpp"

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
    // glEnable(GL_DEPTH_TEST);    // used for z-buffer 
}

void Game::setup() {
    // AssetManager ............................................................
    m_assetManager.setVShader("vert", "../assets/shaders/v.vert");
    m_assetManager.setFShader("frag", "../assets/shaders/f.frag");
    m_assetManager.setTexture("regularOctagon", "../assets/textures/polygons/octagon.png"); 
    m_assetManager.setTexture("awesomeface", "../assets/textures/awesomeface.png");

    unsigned int vertex = m_assetManager.getVShader("vert");
    unsigned int fragment = m_assetManager.getFShader("frag");
    m_assetManager.setShaderProgram("vert&frag", vertex, fragment);

    // Box2D ...................................................................
    // make bottom static box
    BodyPolygonComponent bottomBox;
    bottomBox.m_bodyDef.position.Set(0.0f, -10.0f);
    bottomBox.m_body = m_world->CreateBody(&bottomBox.m_bodyDef);
    bottomBox.m_polygonShape.SetAsBox(50.0f, 10.0f);
    bottomBox.m_body->CreateFixture(&bottomBox.m_polygonShape, 0.0f);

    // make dynamic octagon
    BodyPolygonComponent octagon;
    ShapeOctagonComponent octagonShape;
    TextureComponent octagonTexture = TextureComponent(m_assetManager.getTexture("awesomeface"));
    ShaderProgramComponent octagonShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("vert&frag"));
    RenderBuffersComponent octagonBuffers;
    octagon.m_bodyDef.type = b2_dynamicBody;
    octagon.m_bodyDef.position.Set(6.0f, 4.0f);
    octagon.m_body = m_world->CreateBody(&octagon.m_bodyDef);
    octagon.m_polygonShape.Set(octagonShape.m_vertices, octagonShape.m_vertexCount);
    octagon.m_fixtureDef.shape = &octagon.m_polygonShape;
    octagon.m_fixtureDef.density = 1.0f;
    octagon.m_fixtureDef.friction = 0.3f;
    octagon.m_body->CreateFixture(&octagon.m_fixtureDef);

    /*
    // make test object
    ShapeTestComponent testShape;
    TextureComponent testTexture = TextureComponent(m_assetManager.getTexture("awesomeface"));
    ShaderProgramComponent testShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("vert&frag"));
    RenderBuffersComponent testBuffers;
    */

    // EnTT ....................................................................
    auto groundEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(groundEntity, bottomBox);

    auto octagonEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(octagonEntity, octagon);
    m_registry.emplace<ShapeOctagonComponent>(octagonEntity, octagonShape);
    m_registry.emplace<TextureComponent>(octagonEntity, octagonTexture);
    m_registry.emplace<ShaderProgramComponent>(octagonEntity, octagonShaderProgram);

    /*
    auto testEntity = m_registry.create();
    m_registry.emplace<TextureComponent>(testEntity, testTexture);
    m_registry.emplace<ShaderProgramComponent>(testEntity, testShaderProgram);
    */

    // BIG TEST TIME ***********************************************************
    // *************************************************************************
    // *************************************************************************
    // *************************************************************************
    // *************************************************************************
    glGenVertexArrays(1, &octagonBuffers.m_VAO);
    glGenBuffers(1, &octagonBuffers.m_VBO);
    glGenBuffers(1, &octagonBuffers.m_EBO);

    glBindVertexArray(octagonBuffers.m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, octagonBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(octagonShape.m_verticesRender), octagonShape.m_verticesRender, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, octagonBuffers.m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(octagonShape.m_indices), octagonShape.m_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_registry.emplace<RenderBuffersComponent>(octagonEntity, octagonBuffers);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(octagonShaderProgram.m_shaderProgram);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(octagonShaderProgram.m_shaderProgram, "ourTexture"), 0);
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
    //m_movementSystem.update(timeStep, m_registry);
}

void Game::render(float renderFactor) {
    // specify color values to then use in filling color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // R, G, B, Alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderSystem.update(renderFactor, m_registry);

    // swap front and back buffers (drawing to back buffer, displaying front)
    glfwSwapBuffers(m_window.m_glfwWindow);
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Post - Game Loop

void Game::destroy() {
}
