// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_game.cpp
//  implementation of Game class, controls game loop  
// -----------------------------------------------------------------------------

#include "core_game.h"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Pre - Game Loop
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void Game::initialize() {
    m_isRunning = true;

    m_logManager.initialize();
    ONSET_INFO("ONSET ENGINE v{}.{}.{}", 0, 1, 0);
    // defining engine config in core_game.h
#ifdef ONSET_CONFIG_DEBUG
    ONSET_INFO("CONFIGURATION: DEBUG");
#endif
#ifdef ONSET_CONFIG_RELEASE
    ONSET_INFO("CONFIGURATION: RELEASE");
#endif

    m_windowManager = std::make_unique<WindowManager>();
    m_windowManager->initialize(m_screenWidth, m_screenHeight);

    m_inputInvoker = std::make_unique<InputInvoker>();
    m_inputInvoker->initialize(
        m_windowManager->m_glfwWindow, 
        &m_registry, 
        m_screenWidth, 
        m_screenHeight
    );
}

void Game::setup() {
    // AssetManager ............................................................
    m_assetManager.setVShader("vert", "../assets/shaders/v.vert");
    m_assetManager.setFShader("frag", "../assets/shaders/f.frag");
    m_assetManager.setVShader("lightvert", "../assets/shaders/light.vert");
    m_assetManager.setFShader("lightfrag", "../assets/shaders/light.frag");
    m_assetManager.setVShader("colorvert", "../assets/shaders/color.vert");
    m_assetManager.setFShader("colorfrag", "../assets/shaders/color.frag");
    m_assetManager.setTexture("orion", "../assets/textures/orion.jpg");
    m_assetManager.setTexture("milkyway", "../assets/textures/milkyway.jpg");
    m_assetManager.setTexture("stripes", "../assets/textures/stripes.jpg");
    m_assetManager.setTexture("rusteddiffuse", "../assets/textures/freepbr/rustediron2_basecolor.png");
    m_assetManager.setTexture("rustedspecular", "../assets/textures/freepbr/rustediron2_metallic.png");
    m_assetManager.setTexture("blackspecular", "../assets/textures/black.jpg");


    unsigned int vertex = m_assetManager.getVShader("vert");
    unsigned int fragment = m_assetManager.getFShader("frag");
    m_assetManager.setShaderProgram("vert&frag", vertex, fragment);
    vertex = m_assetManager.getVShader("lightvert");
    fragment = m_assetManager.getFShader("lightfrag");
    m_assetManager.setShaderProgram("light", vertex, fragment);
    vertex = m_assetManager.getVShader("colorvert");
    fragment = m_assetManager.getFShader("colorfrag");
    m_assetManager.setShaderProgram("color", vertex, fragment);

    // Prepare Entities ........................................................
    // make a camera 
    CameraComponent camera(glm::vec3(0.0f, 0.0f, 20.0f));

    // make a light source (sphere/point)
    LightComponent lightLight;
    BodyCircleComponent lightBody;
    MeshSphereComponent lightMesh;
    ShaderProgramComponent lightShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("light"));
    RenderBuffersComponent lightBuffers;
    lightBody.m_bodyDef.type = b2_dynamicBody;
    lightBody.m_bodyDef.position.Set(-10.0f, 5.0f);
    lightBody.m_body = m_world->CreateBody(&lightBody.m_bodyDef);
    // sphereBody.m_body->SetFixedRotation(true);
    lightBody.m_circleShape.m_p.Set(0.0f, 0.0f);
    lightBody.m_circleShape.m_radius = 0.5f;
    lightBody.m_fixtureDef.shape = &lightBody.m_circleShape;
    lightBody.m_fixtureDef.density = 1.0f;
    lightBody.m_fixtureDef.friction = 0.3f;
    lightBody.m_body->CreateFixture(&lightBody.m_fixtureDef);
    glGenVertexArrays(1, &lightBuffers.m_VAO);
    glGenBuffers(1, &lightBuffers.m_VBO);
    glBindVertexArray(lightBuffers.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, lightMesh.m_verticesSize, lightMesh.m_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // make a sphere to test color (reflects the light source)
    ColorComponent colorColor;
    BodyCircleComponent colorBody;
    MeshSphereComponent colorMesh;
    TextureComponent colorTexture = TextureComponent(m_assetManager.getTexture("rusteddiffuse"), m_assetManager.getTexture("rustedspecular"));
    ShaderProgramComponent colorShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("color"));
    RenderBuffersComponent colorBuffers;
    colorBody.m_bodyDef.type = b2_dynamicBody;
    colorBody.m_bodyDef.position.Set(-5.0f, 5.0f);
    colorBody.m_body = m_world->CreateBody(&colorBody.m_bodyDef);
    // sphereBody.m_body->SetFixedRotation(true);
    colorBody.m_circleShape.m_p.Set(0.0f, 0.0f);
    colorBody.m_circleShape.m_radius = 1.0f;
    colorBody.m_fixtureDef.shape = &colorBody.m_circleShape;
    colorBody.m_fixtureDef.density = 1.0f;
    colorBody.m_fixtureDef.friction = 0.3f;
    colorBody.m_body->CreateFixture(&colorBody.m_fixtureDef);
    glGenVertexArrays(1, &colorBuffers.m_VAO);
    glGenBuffers(1, &colorBuffers.m_VBO);
    glBindVertexArray(colorBuffers.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffers.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, colorMesh.m_verticesSize, colorMesh.m_vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(colorShaderProgram.m_shaderProgram);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(colorShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    // set it manually like so:
    glUniform1i(glGetUniformLocation(colorShaderProgram.m_shaderProgram, "material.specular"), 1);

    // make bottom static box
    BodyPolygonComponent groundBody;
    MeshGroundComponent groundMesh;
    TextureComponent groundTexture = TextureComponent(m_assetManager.getTexture("stripes"), m_assetManager.getTexture("blackspecular"));
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
    // normal attribute
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
    TextureComponent cubeTexture = TextureComponent(m_assetManager.getTexture("milkyway"), m_assetManager.getTexture("blackspecular"));
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
    // normal attribute
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
    TextureComponent sphereTexture = TextureComponent(m_assetManager.getTexture("orion"), m_assetManager.getTexture("blackspecular"));
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
    // normal attribute
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
    auto cameraEntity = m_registry.create();
    m_registry.emplace<CameraComponent>(cameraEntity, camera);

    auto lightEntity = m_registry.create();
    m_registry.emplace<LightComponent>(lightEntity, lightLight);
    m_registry.emplace<BodyCircleComponent>(lightEntity, lightBody);
    m_registry.emplace<MeshSphereComponent>(lightEntity, lightMesh);
    m_registry.emplace<ShaderProgramComponent>(lightEntity, lightShaderProgram);
    m_registry.emplace<RenderBuffersComponent>(lightEntity, lightBuffers);

    auto colorEntity = m_registry.create();
    m_registry.emplace<ColorComponent>(colorEntity, colorColor);
    m_registry.emplace<BodyCircleComponent>(colorEntity, colorBody);
    m_registry.emplace<MeshSphereComponent>(colorEntity, colorMesh);
    m_registry.emplace<TextureComponent>(colorEntity, colorTexture);
    m_registry.emplace<ShaderProgramComponent>(colorEntity, colorShaderProgram);
    m_registry.emplace<RenderBuffersComponent>(colorEntity, colorBuffers);

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

void Game::run() {
    // glfwWindowShouldClose() returns GL_FALSE until window instructed to close
    while (!glfwWindowShouldClose(m_windowManager->m_glfwWindow) && m_isRunning) {
        // find time-step 
        double currentTime = glfwGetTime();    // returns time in secs
        double deltaTime = currentTime - previousTime;
        // cap the max number of Update() looping - to prevent locking up
        if (deltaTime > 0.25) {
            deltaTime = 0.25;   // max of 25 loops, since SECS_PER_UPDATE = 0.01 
            ONSET_WARN("The calculated deltaTime exceeded 0.25 seconds");
        }
        previousTime = currentTime;
        lag += deltaTime;

        // game loop
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
}

void Game::update(const float timeStep, const int32 velocityIterations, const int32 positionIterations) {
    // box2D update
    m_world->Step(timeStep, velocityIterations, positionIterations);
    m_cameraSystem.update(timeStep, m_registry);
}

void Game::render(const float renderFactor) {
    // specify color values to then use in filling color buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);   // R, G, B, Alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderSystem.update(renderFactor, m_registry, m_screenWidth, m_screenHeight);

    // swap front and back buffers (drawing to back buffer, displaying front)
    glfwSwapBuffers(m_windowManager->m_glfwWindow);
    // call window and input callbacks associated with these events
    glfwPollEvents();
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Post - Game Loop
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void Game::destroy() {
    // temporarily deleting buffers, assets, entities here for now
    // TODO: will need to use these methods between game levels
    m_renderSystem.deleteBuffers(m_registry);
    m_assetManager.deleteAssets();
    
    m_inputInvoker->destroy();
    m_windowManager->destroy();
    m_logManager.destroy();
}