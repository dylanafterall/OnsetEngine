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
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // Assets
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // meshes
    // .........................................................................
    MeshCubeComponent cubeMesh;
    MeshSphereComponent sphereMesh;
    MeshGroundComponent groundMesh;
    // shaders
    // .........................................................................
    m_assetManager.setVShader("light_vert", "../assets/shaders/light.vert");
    m_assetManager.setFShader("light_frag", "../assets/shaders/light.frag");
    m_assetManager.setVShader("surface_vert", "../assets/shaders/surface.vert");
    m_assetManager.setFShader("surface_frag", "../assets/shaders/surface.frag");
    m_assetManager.setVShader("stencil_vert", "../assets/shaders/stencil.vert");
    m_assetManager.setFShader("stencil_frag", "../assets/shaders/stencil.frag");
    // shader programs
    // .........................................................................
    unsigned int vertex = m_assetManager.getVShader("light_vert");
    unsigned int fragment = m_assetManager.getFShader("light_frag");
    m_assetManager.setShaderProgram("light", vertex, fragment);
    vertex = m_assetManager.getVShader("surface_vert");
    fragment = m_assetManager.getFShader("surface_frag");
    m_assetManager.setShaderProgram("surface", vertex, fragment);
    vertex = m_assetManager.getVShader("stencil_vert");
    fragment = m_assetManager.getFShader("stencil_frag");
    m_assetManager.setShaderProgram("stencil", vertex, fragment);
    // texture maps
    // .........................................................................
    m_assetManager.setTexture("tiles_diff", "../assets/textures/black-white-tile_albedo.png");
    m_assetManager.setTexture("tiles_spec", "../assets/textures/black-white-tile_metallic.png");
    m_assetManager.setTexture("rusted_diff", "../assets/textures/rusted-steel_albedo.png");
    m_assetManager.setTexture("rusted_spec", "../assets/textures/rusted-steel_metallic.png");
    m_assetManager.setTexture("blocks_diff", "../assets/textures/angled-blocks-vegetation_albedo.png");
    m_assetManager.setTexture("blocks_spec", "../assets/textures/angled-blocks-vegetation_metallic.png");
    m_assetManager.setTexture("metal_diff", "../assets/textures/dull_metal_albedo.png");
    m_assetManager.setTexture("metal_spec", "../assets/textures/dull_metal_metallic.png");

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // Entities
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // camera entity
    // .........................................................................
    // setup components
    CameraComponent camera(glm::vec3(0.0f, 0.0f, 20.0f));
    camera.m_type = first;

    // sunLight entity (pointed down, white light)
    // .........................................................................
    // setup components
    LightComponent sunLightLight;
    BodyTransformComponent sunLightTransform;
    ShaderProgramComponent sunLightShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("light"), m_assetManager.getShaderProgram("stencil"));
    ReflectorShaderProgramComponent sunLightReflectorProgram = ReflectorShaderProgramComponent(m_assetManager.getShaderProgram("surface"));
    RenderDataComponent sunLightGraphics;
    sunLightLight.m_type = 0;               // directional type
    sunLightLight.m_direction[0] = 0.0f;    // pointed down
    sunLightLight.m_direction[1] = -1.0f;
    sunLightLight.m_direction[2] = 0.0f;
    sunLightLight.m_ambient[0] = 0.5f;      // white ambient light
    sunLightLight.m_ambient[1] = 0.5f;
    sunLightLight.m_ambient[2] = 0.5f;
    sunLightLight.m_diffuse[0] = 0.5f;      // white diffuse light
    sunLightLight.m_diffuse[1] = 0.5f;
    sunLightLight.m_diffuse[2] = 0.5f;
    sunLightLight.m_specular[0] = 0.5f;     // white specular light
    sunLightLight.m_specular[1] = 0.5f;
    sunLightLight.m_specular[2] = 0.5f;

    // blueLight entity (dynamic point source, blue light)
    // .........................................................................
    // setup components
    LightComponent blueLightLight;
    BodyTransformComponent blueLightTransform;
    BodyCircleComponent blueLightCircle;
    ShaderProgramComponent blueLightShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("light"), m_assetManager.getShaderProgram("stencil"));
    ReflectorShaderProgramComponent blueLightReflectorProgram = ReflectorShaderProgramComponent(m_assetManager.getShaderProgram("surface"));
    RenderDataComponent blueLightGraphics;
    blueLightLight.m_type = 1;              // point type 
    blueLightLight.m_scale[0] = 0.5f;       // ensure Box2D radius matches this
    blueLightLight.m_scale[1] = 0.5f;
    blueLightLight.m_scale[2] = 0.5f;
    blueLightLight.m_constant = 1.0f;
    blueLightLight.m_linear = 0.09f;
    blueLightLight.m_quadratic = 0.032f;
    blueLightLight.m_ambient[0] = 0.0f;     // blue ambient light
    blueLightLight.m_ambient[1] = 0.0f;
    blueLightLight.m_ambient[2] = 1.0f;
    blueLightLight.m_diffuse[0] = 0.0f;     // blue diffuse light
    blueLightLight.m_diffuse[1] = 0.0f;
    blueLightLight.m_diffuse[2] = 1.0f;
    blueLightLight.m_specular[0] = 0.0f;    // blue specular light
    blueLightLight.m_specular[1] = 0.0f;
    blueLightLight.m_specular[2] = 1.0f;
    blueLightGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    blueLightCircle.m_bodyDef.type = b2_dynamicBody;
    blueLightCircle.m_bodyDef.position.Set(-15.0f, 5.0f);
    blueLightTransform.m_body = m_world->CreateBody(&blueLightCircle.m_bodyDef);
    blueLightCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    blueLightCircle.m_circleShape.m_radius = 0.5f;
    blueLightCircle.m_fixtureDef.shape = &blueLightCircle.m_circleShape;
    blueLightCircle.m_fixtureDef.density = 1.0f;
    blueLightCircle.m_fixtureDef.friction = 0.3f;
    blueLightTransform.m_body->CreateFixture(&blueLightCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &blueLightGraphics.m_VAO);
    glGenBuffers(1, &blueLightGraphics.m_VBO);
    glBindVertexArray(blueLightGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, blueLightGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // greenLight entity (dynamic point source, green light)
    // .........................................................................
    // setup components
    LightComponent greenLightLight;
    BodyTransformComponent greenLightTransform;
    BodyCircleComponent greenLightCircle;
    ShaderProgramComponent greenLightShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("light"), m_assetManager.getShaderProgram("stencil"));
    ReflectorShaderProgramComponent greenLightReflectorProgram = ReflectorShaderProgramComponent(m_assetManager.getShaderProgram("surface"));
    RenderDataComponent greenLightGraphics;
    greenLightLight.m_type = 1;             // point type
    greenLightLight.m_scale[0] = 1.5f;      // ensure Box2D radius matches this
    greenLightLight.m_scale[1] = 1.5f;
    greenLightLight.m_scale[2] = 1.5f;
    greenLightLight.m_constant = 1.0f;
    greenLightLight.m_linear = 0.09f;
    greenLightLight.m_quadratic = 0.032f;
    greenLightLight.m_ambient[0] = 0.0f;    // green ambient light
    greenLightLight.m_ambient[1] = 1.0f;
    greenLightLight.m_ambient[2] = 0.0f;
    greenLightLight.m_diffuse[0] = 0.0f;    // green diffuse light
    greenLightLight.m_diffuse[1] = 1.0f;
    greenLightLight.m_diffuse[2] = 0.0f;
    greenLightLight.m_specular[0] = 0.0f;   // green specular light
    greenLightLight.m_specular[1] = 1.0f;
    greenLightLight.m_specular[2] = 0.0f;
    greenLightGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    greenLightCircle.m_bodyDef.type = b2_dynamicBody;
    greenLightCircle.m_bodyDef.position.Set(10.0f, 5.0f);
    greenLightTransform.m_body = m_world->CreateBody(&greenLightCircle.m_bodyDef);
    greenLightCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    greenLightCircle.m_circleShape.m_radius = 1.5f;
    greenLightCircle.m_fixtureDef.shape = &greenLightCircle.m_circleShape;
    greenLightCircle.m_fixtureDef.density = 1.0f;
    greenLightCircle.m_fixtureDef.friction = 0.3f;
    greenLightTransform.m_body->CreateFixture(&greenLightCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &greenLightGraphics.m_VAO);
    glGenBuffers(1, &greenLightGraphics.m_VBO);
    glBindVertexArray(greenLightGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, greenLightGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // streetLight entity (pointed down, yellow light)
    // .........................................................................
    // setup components
    LightComponent streetLightLight;
    BodyTransformComponent streetLightTransform;
    BodyCircleComponent streetLightCircle;
    ShaderProgramComponent streetLightShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("light"), m_assetManager.getShaderProgram("stencil"));
    ReflectorShaderProgramComponent streetLightReflectorProgram = ReflectorShaderProgramComponent(m_assetManager.getShaderProgram("surface"));
    RenderDataComponent streetLightGraphics;
    streetLightLight.m_type = 2;                // spot type
    streetLightLight.m_scale[0] = 1.0f;         // ensure Box2D radius matches this
    streetLightLight.m_scale[1] = 1.0f;
    streetLightLight.m_scale[2] = 1.0f;
    streetLightLight.m_direction[0] = 0.0f;     // pointed down
    streetLightLight.m_direction[1] = -1.0f;
    streetLightLight.m_direction[2] = 0.0f;
    streetLightLight.m_cutOff = glm::cos(glm::radians(12.5f));
    streetLightLight.m_outerCutOff = glm::cos(glm::radians(15.0f));
    streetLightLight.m_constant = 1.0f;
    streetLightLight.m_linear = 0.09f;
    streetLightLight.m_quadratic = 0.032f;
    streetLightLight.m_ambient[0] = 0.0f;       // no ambient light
    streetLightLight.m_ambient[1] = 0.0f;
    streetLightLight.m_ambient[2] = 0.0f;
    streetLightLight.m_diffuse[0] = 1.0f;       // yellow diffuse light
    streetLightLight.m_diffuse[1] = 1.0f;
    streetLightLight.m_diffuse[2] = 0.0f;
    streetLightLight.m_specular[0] = 1.0f;      // yellow specular light
    streetLightLight.m_specular[1] = 1.0f;
    streetLightLight.m_specular[2] = 0.0f;
    streetLightGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    streetLightCircle.m_bodyDef.position.Set(-10.0f, 10.0f);
    streetLightTransform.m_body = m_world->CreateBody(&streetLightCircle.m_bodyDef);
    streetLightCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    streetLightCircle.m_circleShape.m_radius = 1.0f;
    streetLightCircle.m_fixtureDef.shape = &streetLightCircle.m_circleShape;
    streetLightCircle.m_fixtureDef.density = 1.0f;
    streetLightCircle.m_fixtureDef.friction = 0.3f;
    streetLightTransform.m_body->CreateFixture(&streetLightCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &streetLightGraphics.m_VAO);
    glGenBuffers(1, &streetLightGraphics.m_VBO);
    glBindVertexArray(streetLightGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, streetLightGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // player entity (dynamic, marble-textured sphere)
    // .........................................................................
    // setup components
    PlayerComponent playerPlayer;
    MaterialComponent playerMaterial;
    BodyTransformComponent playerTransform;
    BodyCircleComponent playerCircle;
    TextureComponent playerTexture = TextureComponent(m_assetManager.getTexture("tiles_diff"), m_assetManager.getTexture("tiles_spec"));
    ShaderProgramComponent playerShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("surface"), m_assetManager.getShaderProgram("stencil"));
    RenderDataComponent playerGraphics;
    playerMaterial.m_shininess = 128.0f;
    playerGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    playerGraphics.m_stencilFlag = true;
    // setup Box2D data
    playerCircle.m_bodyDef.type = b2_dynamicBody;
    playerCircle.m_bodyDef.position.Set(0.0f, 5.0f);
    playerTransform.m_body = m_world->CreateBody(&playerCircle.m_bodyDef);
    playerCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    playerCircle.m_circleShape.m_radius = 1.0f;
    playerCircle.m_fixtureDef.shape = &playerCircle.m_circleShape;
    playerCircle.m_fixtureDef.density = 1.0f;
    playerCircle.m_fixtureDef.friction = 0.3f;
    playerTransform.m_body->CreateFixture(&playerCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &playerGraphics.m_VAO);
    glGenBuffers(1, &playerGraphics.m_VBO);
    glBindVertexArray(playerGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, playerGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(playerShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(playerShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(playerShaderProgram.m_shaderProgram, "material.specular"), 1);

    // floor entity (static, tile-textured box)
    // .........................................................................
    // setup components
    MaterialComponent floorMaterial;
    BodyTransformComponent floorTransform;
    BodyPolygonComponent floorPolygon;
    TextureComponent floorTexture = TextureComponent(m_assetManager.getTexture("metal_diff"), m_assetManager.getTexture("metal_spec"));
    ShaderProgramComponent floorShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("surface"), m_assetManager.getShaderProgram("stencil"));
    RenderDataComponent floorGraphics;
    floorMaterial.m_shininess = 32.0f;
    floorGraphics.m_vertexCount = groundMesh.m_vertexCount;
    // setup Box2D data
    floorPolygon.m_bodyDef.position.Set(0.0f, -1.0f);
    floorTransform.m_body = m_world->CreateBody(&floorPolygon.m_bodyDef);
    floorPolygon.m_polygonShape.SetAsBox(50.0f, 1.0f); // (SetAsBox(half-width, half-height))
    floorTransform.m_body->CreateFixture(&floorPolygon.m_polygonShape, 0.0f);
    // setup OpenGL data
    glGenVertexArrays(1, &floorGraphics.m_VAO);
    glGenBuffers(1, &floorGraphics.m_VBO);
    glBindVertexArray(floorGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, groundMesh.m_verticesSize, groundMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(floorShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(floorShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(floorShaderProgram.m_shaderProgram, "material.specular"), 1);

    // sphere entity (dynamic, rust-textured sphere)
    // .........................................................................
    // setup components
    MaterialComponent sphereMaterial;
    BodyTransformComponent sphereTransform;
    BodyCircleComponent sphereCircle;
    TextureComponent sphereTexture = TextureComponent(m_assetManager.getTexture("rusted_diff"), m_assetManager.getTexture("rusted_spec"));
    ShaderProgramComponent sphereShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("surface"), m_assetManager.getShaderProgram("stencil"));
    RenderDataComponent sphereGraphics;
    sphereMaterial.m_shininess = 64.0f;
    sphereGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    sphereGraphics.m_stencilFlag = true;
    // setup Box2D data
    sphereCircle.m_bodyDef.type = b2_dynamicBody;
    sphereCircle.m_bodyDef.position.Set(-5.0f, 5.0f);
    sphereTransform.m_body = m_world->CreateBody(&sphereCircle.m_bodyDef);
    sphereCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    sphereCircle.m_circleShape.m_radius = 1.0f;
    sphereCircle.m_fixtureDef.shape = &sphereCircle.m_circleShape;
    sphereCircle.m_fixtureDef.density = 1.0f;
    sphereCircle.m_fixtureDef.friction = 0.3f;
    sphereTransform.m_body->CreateFixture(&sphereCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &sphereGraphics.m_VAO);
    glGenBuffers(1, &sphereGraphics.m_VBO);
    glBindVertexArray(sphereGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(sphereShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(sphereShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(sphereShaderProgram.m_shaderProgram, "material.specular"), 1);

    // cube entity (dynamic, block-textured cube)
    // .........................................................................
    // setup components
    MaterialComponent cubeMaterial;
    BodyTransformComponent cubeTransform;
    BodyPolygonComponent cubePolygon;
    ShapeSquareComponent cubeShape;
    TextureComponent cubeTexture = TextureComponent(m_assetManager.getTexture("blocks_diff"), m_assetManager.getTexture("blocks_spec"));
    ShaderProgramComponent cubeShaderProgram = ShaderProgramComponent(m_assetManager.getShaderProgram("surface"), m_assetManager.getShaderProgram("stencil"));
    RenderDataComponent cubeGraphics;
    cubeMaterial.m_shininess = 32.0f;
    cubeGraphics.m_vertexCount = cubeMesh.m_vertexCount;
    cubeGraphics.m_stencilFlag = true;
    // setup Box2D data
    cubePolygon.m_bodyDef.type = b2_dynamicBody;
    cubePolygon.m_bodyDef.position.Set(5.0f, 5.0f);
    cubeTransform.m_body = m_world->CreateBody(&cubePolygon.m_bodyDef);
    cubePolygon.m_polygonShape.Set(cubeShape.m_vertices, cubeShape.m_vertexCount);
    cubePolygon.m_fixtureDef.shape = &cubePolygon.m_polygonShape;
    cubePolygon.m_fixtureDef.density = 1.0f;
    cubePolygon.m_fixtureDef.friction = 0.3f;
    cubeTransform.m_body->CreateFixture(&cubePolygon.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &cubeGraphics.m_VAO);
    glGenBuffers(1, &cubeGraphics.m_VBO);
    glBindVertexArray(cubeGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeMesh.m_verticesSize, cubeMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(cubeShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(cubeShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(cubeShaderProgram.m_shaderProgram, "material.specular"), 1);

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // Registry
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto cameraEntity = m_registry.create();
    m_registry.emplace<CameraComponent>(cameraEntity, camera);

    auto sunLightEntity = m_registry.create();
    m_registry.emplace<LightComponent>(sunLightEntity, sunLightLight);
    m_registry.emplace<BodyTransformComponent>(sunLightEntity, sunLightTransform);
    m_registry.emplace<ShaderProgramComponent>(sunLightEntity, sunLightShaderProgram);
    m_registry.emplace<ReflectorShaderProgramComponent>(sunLightEntity, sunLightReflectorProgram);
    m_registry.emplace<RenderDataComponent>(sunLightEntity, sunLightGraphics);

    auto blueLightEntity = m_registry.create();
    m_registry.emplace<LightComponent>(blueLightEntity, blueLightLight);
    m_registry.emplace<BodyTransformComponent>(blueLightEntity, blueLightTransform);
    m_registry.emplace<ShaderProgramComponent>(blueLightEntity, blueLightShaderProgram);
    m_registry.emplace<ReflectorShaderProgramComponent>(blueLightEntity, blueLightReflectorProgram);
    m_registry.emplace<RenderDataComponent>(blueLightEntity, blueLightGraphics);

    auto greenLightEntity = m_registry.create();
    m_registry.emplace<LightComponent>(greenLightEntity, greenLightLight);
    m_registry.emplace<BodyTransformComponent>(greenLightEntity, greenLightTransform);
    m_registry.emplace<ShaderProgramComponent>(greenLightEntity, greenLightShaderProgram);
    m_registry.emplace<ReflectorShaderProgramComponent>(greenLightEntity, greenLightReflectorProgram);
    m_registry.emplace<RenderDataComponent>(greenLightEntity, greenLightGraphics);

    auto streetLightEntity = m_registry.create();
    m_registry.emplace<LightComponent>(streetLightEntity, streetLightLight);
    m_registry.emplace<BodyTransformComponent>(streetLightEntity, streetLightTransform);
    m_registry.emplace<BodyCircleComponent>(streetLightEntity, streetLightCircle);
    m_registry.emplace<ShaderProgramComponent>(streetLightEntity, streetLightShaderProgram);
    m_registry.emplace<ReflectorShaderProgramComponent>(streetLightEntity, streetLightReflectorProgram);
    m_registry.emplace<RenderDataComponent>(streetLightEntity, streetLightGraphics);

    auto playerEntity = m_registry.create();
    m_registry.emplace<PlayerComponent>(playerEntity, playerPlayer);
    m_registry.emplace<MaterialComponent>(playerEntity, playerMaterial);
    m_registry.emplace<BodyTransformComponent>(playerEntity, playerTransform);
    m_registry.emplace<TextureComponent>(playerEntity, playerTexture);
    m_registry.emplace<ShaderProgramComponent>(playerEntity, playerShaderProgram);
    m_registry.emplace<RenderDataComponent>(playerEntity, playerGraphics);

    auto floorEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(floorEntity, floorMaterial);
    m_registry.emplace<BodyTransformComponent>(floorEntity, floorTransform);
    m_registry.emplace<TextureComponent>(floorEntity, floorTexture);
    m_registry.emplace<ShaderProgramComponent>(floorEntity, floorShaderProgram);
    m_registry.emplace<RenderDataComponent>(floorEntity, floorGraphics);

    auto sphereEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(sphereEntity, sphereMaterial);
    m_registry.emplace<BodyTransformComponent>(sphereEntity, sphereTransform);
    m_registry.emplace<TextureComponent>(sphereEntity, sphereTexture);
    m_registry.emplace<ShaderProgramComponent>(sphereEntity, sphereShaderProgram);
    m_registry.emplace<RenderDataComponent>(sphereEntity, sphereGraphics);

    auto cubeEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(cubeEntity, cubeMaterial);
    m_registry.emplace<BodyTransformComponent>(cubeEntity, cubeTransform);
    m_registry.emplace<TextureComponent>(cubeEntity, cubeTexture);
    m_registry.emplace<ShaderProgramComponent>(cubeEntity, cubeShaderProgram);
    m_registry.emplace<RenderDataComponent>(cubeEntity, cubeGraphics);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
    m_registry.clear();
    
    m_inputInvoker->destroy();
    m_windowManager->destroy();
    m_logManager.destroy();
}