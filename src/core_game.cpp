// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.cpp
//  implementation of Game class, controls game loop  
// -----------------------------------------------------------------------------

#include "core_game.hpp"
#include "component_all.hpp"

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
    BodyPolygonComponent bottomBox;
    bottomBox.m_bodyDef.position.Set(0.0f, -10.0f);
    bottomBox.m_body = m_world->CreateBody(&bottomBox.m_bodyDef);
    bottomBox.m_polygonShape.SetAsBox(50.0f, 10.0f);
    bottomBox.m_body->CreateFixture(&bottomBox.m_polygonShape, 0.0f);

    // make dynamic triangle
    BodyPolygonComponent triangle;
    ShapeTriangleComponent triangleShape;
    triangle.m_bodyDef.type = b2_dynamicBody;
    triangle.m_bodyDef.position.Set(-9.0f, 4.0f);
    triangle.m_body = m_world->CreateBody(&triangle.m_bodyDef);
    triangle.m_polygonShape.Set(triangleShape.m_vertices, triangleShape.m_vertexCount);
    triangle.m_fixtureDef.shape = &triangle.m_polygonShape;
    triangle.m_fixtureDef.density = 1.0f;
    triangle.m_fixtureDef.friction = 0.3f;
    triangle.m_body->CreateFixture(&triangle.m_fixtureDef);

    // make dynamic square
    BodyPolygonComponent square;
    ShapeSquareComponent squareShape;
    square.m_bodyDef.type = b2_dynamicBody;
    square.m_bodyDef.position.Set(-6.0f, 4.0f);
    square.m_body = m_world->CreateBody(&square.m_bodyDef);
    square.m_polygonShape.Set(squareShape.m_vertices, squareShape.m_vertexCount);
    square.m_fixtureDef.shape = &square.m_polygonShape;
    square.m_fixtureDef.density = 1.0f;
    square.m_fixtureDef.friction = 0.3f;
    square.m_body->CreateFixture(&square.m_fixtureDef);

    // make dynamic pentagon
    BodyPolygonComponent pentagon; 
    ShapePentagonComponent pentagonShape;
    pentagon.m_bodyDef.type = b2_dynamicBody;
    pentagon.m_bodyDef.position.Set(-3.0f, 4.0f);
    pentagon.m_body = m_world->CreateBody(&pentagon.m_bodyDef);
    pentagon.m_polygonShape.Set(pentagonShape.m_vertices, pentagonShape.m_vertexCount);
    pentagon.m_fixtureDef.shape = &pentagon.m_polygonShape;
    pentagon.m_fixtureDef.density = 1.0f;
    pentagon.m_fixtureDef.friction = 0.3f;
    pentagon.m_body->CreateFixture(&pentagon.m_fixtureDef);
    
    // make dynamic hexagon
    BodyPolygonComponent hexagon;
    ShapeHexagonComponent hexagonShape;
    hexagon.m_bodyDef.type = b2_dynamicBody;
    hexagon.m_bodyDef.position.Set(0.0f, 4.0f);
    hexagon.m_body = m_world->CreateBody(&hexagon.m_bodyDef);
    hexagon.m_polygonShape.Set(hexagonShape.m_vertices, hexagonShape.m_vertexCount);
    hexagon.m_fixtureDef.shape = &hexagon.m_polygonShape;
    hexagon.m_fixtureDef.density = 1.0f;
    hexagon.m_fixtureDef.friction = 0.3f;
    hexagon.m_body->CreateFixture(&hexagon.m_fixtureDef);

    // make dynamic heptagon
    BodyPolygonComponent heptagon;
    ShapeHeptagonComponent heptagonShape;
    heptagon.m_bodyDef.type = b2_dynamicBody;
    heptagon.m_bodyDef.position.Set(3.0f, 4.0f);
    heptagon.m_body = m_world->CreateBody(&heptagon.m_bodyDef);
    heptagon.m_polygonShape.Set(heptagonShape.m_vertices, heptagonShape.m_vertexCount);
    heptagon.m_fixtureDef.shape = &heptagon.m_polygonShape;
    heptagon.m_fixtureDef.density = 1.0f;
    heptagon.m_fixtureDef.friction = 0.3f;
    heptagon.m_body->CreateFixture(&heptagon.m_fixtureDef);

    // make dynamic octagon
    BodyPolygonComponent octagon;
    ShapeOctagonComponent octagonShape; 
    octagon.m_bodyDef.type = b2_dynamicBody;
    octagon.m_bodyDef.position.Set(6.0f, 4.0f);
    octagon.m_body = m_world->CreateBody(&octagon.m_bodyDef);
    octagon.m_polygonShape.Set(octagonShape.m_vertices, octagonShape.m_vertexCount);
    octagon.m_fixtureDef.shape = &octagon.m_polygonShape;
    octagon.m_fixtureDef.density = 1.0f;
    octagon.m_fixtureDef.friction = 0.3f;
    octagon.m_body->CreateFixture(&octagon.m_fixtureDef);

    // make dynamic circle
    BodyCircleComponent circle;
    circle.m_bodyDef.type = b2_dynamicBody;
    circle.m_bodyDef.position.Set(9.0f, 4.0f);
    circle.m_body = m_world->CreateBody(&circle.m_bodyDef);
    circle.m_circleShape.m_p.Set(0.0f, 0.0f);
    circle.m_circleShape.m_radius = 0.5642f;
    circle.m_fixtureDef.shape = &circle.m_circleShape;
    circle.m_fixtureDef.density = 1.0f;
    circle.m_fixtureDef.friction = 0.3f;
    circle.m_body->CreateFixture(&circle.m_fixtureDef);

    // EnTT ....................................................................
    auto player = m_registry.create();
    m_registry.emplace<TextureComponent>(player, m_assetManager.getTexture("container"));
    m_registry.emplace<ShaderProgramComponent>(player, m_assetManager.getShaderProgram("vert&frag"));

    auto groundEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(groundEntity, bottomBox);

    auto triangleEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(triangleEntity, triangle);
    auto squareEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(squareEntity, square);
    auto pentagonEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(pentagonEntity, pentagon);
    auto hexagonEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(hexagonEntity, hexagon);
    auto heptagonEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(heptagonEntity, heptagon);
    auto octagonEntity = m_registry.create();
    m_registry.emplace<BodyPolygonComponent>(octagonEntity, octagon);
    auto circleEntity = m_registry.create();
    m_registry.emplace<BodyCircleComponent>(circleEntity, circle);
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
