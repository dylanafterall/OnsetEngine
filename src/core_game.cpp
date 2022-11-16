// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.cpp
//  implementation of Game class, controls game loop  
// -----------------------------------------------------------------------------

#include "core_game.h"
#include "component_all.h"

#include "GLFW/glfw3.h"

#include "spdlog/spdlog.h"
#include "glm/glm.hpp"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Constructor and Destructor
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// Game(): ---------------------------------------------------------------------
Game::Game() {
    m_windowPtr = new Window(m_screenWidth, m_screenHeight);
    m_invokerPtr = new InputInvoker();
    spdlog::info("Game Constructor called!");
}

// ~Game(): --------------------------------------------------------------------
Game::~Game() {
    delete m_windowPtr;
    delete m_invokerPtr;
    spdlog::info("Game Destructor called!");
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Pre - Game Loop
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// initialize(): ---------------------------------------------------------------
void Game::initialize() {
        // pass our registry to the invoker, for InputCommander execute()'s
    m_invokerPtr->setInvokerRegistry(&m_registry);
    m_invokerPtr->setInvokerAspect(m_screenWidth, m_screenHeight);

    // must set window's invoker before initializing window
    m_windowPtr->setInvoker(m_invokerPtr);
    // initialize GLFW window and GLAD
    m_windowPtr->initialize();

    // create camera component and add to EnTT registry
    CameraComponent camera(glm::vec3(0.0f, 0.0f, 20.0f));
    auto cameraEntity = m_registry.create();
    m_registry.emplace<CameraComponent>(cameraEntity, camera);
}

// setup(): --------------------------------------------------------------------
void Game::setup() {
    // AssetManager ............................................................
    m_assetManager.setVShader("vert", "../assets/shaders/v.vert");
    m_assetManager.setFShader("frag", "../assets/shaders/f.frag");
    m_assetManager.setTexture("orion", "../assets/textures/orion.jpg");
    m_assetManager.setTexture("milkyway", "../assets/textures/milkyway.jpg");
    m_assetManager.setTexture("stripes", "../assets/textures/stripes.jpg");

    unsigned int vertex = m_assetManager.getVShader("vert");
    unsigned int fragment = m_assetManager.getFShader("frag");
    m_assetManager.setShaderProgram("vert&frag", vertex, fragment);

    // Prepare Entities ........................................................
    // make bottom static box
    BodyPolygonComponent groundBody;
    MeshGroundComponent groundMesh;
    TextureComponent groundTexture = TextureComponent(m_assetManager.getTexture("stripes"));
    ShaderProgramComponent groundShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("vert&frag"));
    RenderBuffersComponent groundBuffers;
    groundBody.m_bodyDef.position.Set(0.0f, -1.0f);
    groundBody.m_body = m_world->CreateBody(&groundBody.m_bodyDef);
    groundBody.m_polygonShape.SetAsBox(50.0f, 1.0f); // (SetAsBox(half-width, half-height))
    groundBody.m_body->CreateFixture(&groundBody.m_polygonShape, 0.0f);
    glGenVertexArrays(1, &groundBuffers.m_VAO);
    glGenBuffers(1, &groundBuffers.m_VBO);
    glBindVertexArray(groundBuffers.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, groundMesh.m_verticesSize, groundMesh.m_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(groundShaderProgram.m_shaderProgram);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(groundShaderProgram.m_shaderProgram, "texture1"), 0);

    // make a cube 1) components -> 2) Box2D -> 3) OpenGL
    BodyPolygonComponent cubeBody;
    ShapeSquareComponent cubeShape;
    MeshCubeComponent cubeMesh;
    TextureComponent cubeTexture = TextureComponent(m_assetManager.getTexture("milkyway"));
    ShaderProgramComponent cubeShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("vert&frag"));
    RenderBuffersComponent cubeBuffers;
    cubeBody.m_bodyDef.type = b2_dynamicBody;
    cubeBody.m_bodyDef.position.Set(6.0f, 5.0f);
    cubeBody.m_body = m_world->CreateBody(&cubeBody.m_bodyDef);
    cubeBody.m_polygonShape.Set(cubeShape.m_vertices, cubeShape.m_vertexCount);
    cubeBody.m_fixtureDef.shape = &cubeBody.m_polygonShape;
    cubeBody.m_fixtureDef.density = 1.0f;
    cubeBody.m_fixtureDef.friction = 0.3f;
    cubeBody.m_body->CreateFixture(&cubeBody.m_fixtureDef);
    glGenVertexArrays(1, &cubeBuffers.m_VAO);
    glGenBuffers(1, &cubeBuffers.m_VBO);
    glBindVertexArray(cubeBuffers.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeMesh.m_verticesSize, cubeMesh.m_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(cubeShaderProgram.m_shaderProgram);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(cubeShaderProgram.m_shaderProgram, "texture1"), 0);

    // make a sphere 1) components -> 2) Box2D -> 3) OpenGL
    PlayerComponent spherePlayer;
    BodyCircleComponent sphereBody;
    MeshSphereComponent sphereMesh;
    TextureComponent sphereTexture = TextureComponent(m_assetManager.getTexture("orion"));
    ShaderProgramComponent sphereShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("vert&frag"));
    RenderBuffersComponent sphereBuffers;
    sphereBody.m_bodyDef.type = b2_dynamicBody;
    sphereBody.m_bodyDef.position.Set(0.0f, 5.0f);
    sphereBody.m_body = m_world->CreateBody(&sphereBody.m_bodyDef);
    // sphereBody.m_body->SetFixedRotation(true);
    sphereBody.m_circleShape.m_p.Set(0.0f, 0.0f);
    sphereBody.m_circleShape.m_radius = 1.0f;
    sphereBody.m_fixtureDef.shape = &sphereBody.m_circleShape;
    sphereBody.m_fixtureDef.density = 1.0f;
    sphereBody.m_fixtureDef.friction = 0.3f;
    sphereBody.m_body->CreateFixture(&sphereBody.m_fixtureDef);
    glGenVertexArrays(1, &sphereBuffers.m_VAO);
    glGenBuffers(1, &sphereBuffers.m_VBO);
    glBindVertexArray(sphereBuffers.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(sphereShaderProgram.m_shaderProgram);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(sphereShaderProgram.m_shaderProgram, "texture1"), 0);


    // EnTT ....................................................................
    auto groundEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(groundEntity, groundBody);
    m_registry.emplace<MeshGroundComponent>(groundEntity, groundMesh);
    m_registry.emplace<TextureComponent>(groundEntity, groundTexture);
    m_registry.emplace<ShaderProgramComponent>(groundEntity, groundShaderProgram);
    m_registry.emplace<RenderBuffersComponent>(groundEntity, groundBuffers);

    auto cubeEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(cubeEntity, cubeBody);
    m_registry.emplace<ShapeSquareComponent>(cubeEntity, cubeShape);
    m_registry.emplace<MeshCubeComponent>(cubeEntity, cubeMesh);
    m_registry.emplace<TextureComponent>(cubeEntity, cubeTexture);
    m_registry.emplace<ShaderProgramComponent>(cubeEntity, cubeShaderProgram);
    m_registry.emplace<RenderBuffersComponent>(cubeEntity, cubeBuffers);

    auto sphereEntity = m_registry.create();
    m_registry.emplace<PlayerComponent>(sphereEntity, spherePlayer);
    m_registry.emplace<BodyCircleComponent>(sphereEntity, sphereBody);
    m_registry.emplace<MeshSphereComponent>(sphereEntity, sphereMesh);
    m_registry.emplace<TextureComponent>(sphereEntity, sphereTexture);
    m_registry.emplace<ShaderProgramComponent>(sphereEntity, sphereShaderProgram);
    m_registry.emplace<RenderBuffersComponent>(sphereEntity, sphereBuffers);
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Game Loop
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// run(): ----------------------------------------------------------------------
void Game::run() {
    // glfwWindowShouldClose() returns GL_FALSE until window instructed to close
    while (!glfwWindowShouldClose(m_windowPtr->m_glfwWindow)) {
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

// processInput(): -------------------------------------------------------------
void Game::processInput() {
}

// update(): -------------------------------------------------------------------
void Game::update(const float timeStep, const int32 velocityIterations, const int32 positionIterations) {
    // Box2D simulation
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_cameraSystem.update(timeStep, m_registry);
}

// render(): -------------------------------------------------------------------
void Game::render(float renderFactor) {
    // specify color values to then use in filling color buffer
    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);   // R, G, B, Alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderSystem.update(renderFactor, m_registry, m_screenWidth, m_screenHeight);

    // swap front and back buffers (drawing to back buffer, displaying front)
    glfwSwapBuffers(m_windowPtr->m_glfwWindow);
    // call window and input callbacks associated with these events
    glfwPollEvents();
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Post - Game Loop
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// destroy(): ------------------------------------------------------------------
void Game::destroy() {
    // temporarily deleting buffers here for now
    // TODO: will need to use this method to delete buffers between game levels
    m_renderSystem.deleteBuffers(m_registry);
}