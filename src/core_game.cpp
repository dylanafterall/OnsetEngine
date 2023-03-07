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

    m_renderSystem.setWindowPointer(m_windowManager->m_glfwWindow);
    m_renderSystem.setGammaFlag(true);
    m_renderSystem.setShadowResolution(m_shadowWidth, m_shadowHeight);

    m_world->SetContactListener(&m_collisionSystem);
    m_collisionSystem.setRegistry(&m_registry);
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
    MeshSpriteComponent spriteMesh;
    MeshSkyboxComponent skyboxMesh;
    // shaders
    // .........................................................................
    m_assetManager.setVShader("light_vert", "../assets/shaders/light.vert");
    m_assetManager.setFShader("light_frag", "../assets/shaders/light.frag");
    m_assetManager.setVShader("surface_vert", "../assets/shaders/surface.vert");
    m_assetManager.setFShader("surface_frag", "../assets/shaders/surface.frag");
    m_assetManager.setVShader("stencil_vert", "../assets/shaders/stencil.vert");
    m_assetManager.setFShader("stencil_frag", "../assets/shaders/stencil.frag");
    m_assetManager.setVShader("sprite_vert", "../assets/shaders/sprite.vert");
    m_assetManager.setFShader("sprite_frag", "../assets/shaders/sprite.frag");
    m_assetManager.setVShader("skybox_vert", "../assets/shaders/skybox.vert");
    m_assetManager.setFShader("skybox_frag", "../assets/shaders/skybox.frag");
    m_assetManager.setVShader("shadow_map_vert", "../assets/shaders/shadow_map.vert");
    m_assetManager.setFShader("shadow_map_frag", "../assets/shaders/shadow_map.frag");
    m_assetManager.setVShader("shadow_map_depth_vert", "../assets/shaders/shadow_map_depth.vert");
    m_assetManager.setFShader("shadow_map_depth_frag", "../assets/shaders/shadow_map_depth.frag");

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
    vertex = m_assetManager.getVShader("sprite_vert");
    fragment = m_assetManager.getFShader("sprite_frag");
    m_assetManager.setShaderProgram("sprite", vertex, fragment);
    vertex = m_assetManager.getVShader("skybox_vert");
    fragment = m_assetManager.getFShader("skybox_frag");
    m_assetManager.setShaderProgram("skybox", vertex, fragment);
    vertex = m_assetManager.getVShader("shadow_map_vert");
    fragment = m_assetManager.getFShader("shadow_map_frag");
    m_assetManager.setShaderProgram("shadow_map", vertex, fragment);
    vertex = m_assetManager.getVShader("shadow_map_depth_vert");
    fragment = m_assetManager.getFShader("shadow_map_depth_frag");
    m_assetManager.setShaderProgram("shadow_map_depth", vertex, fragment);

    // texture maps
    // .........................................................................
    m_assetManager.setTexture("tiles_diff", "../assets/textures/black-white-tile_albedo.png", true, true);
    m_assetManager.setTexture("tiles_spec", "../assets/textures/black-white-tile_metallic.png", true, false);
    m_assetManager.setTexture("rusted_diff", "../assets/textures/rusted-steel_albedo.png", true, true);
    m_assetManager.setTexture("rusted_spec", "../assets/textures/rusted-steel_metallic.png", true, false);
    m_assetManager.setTexture("blocks_diff", "../assets/textures/angled-blocks-vegetation_albedo.png", true, true);
    m_assetManager.setTexture("blocks_spec", "../assets/textures/angled-blocks-vegetation_metallic.png", true, false);
    m_assetManager.setTexture("metal_diff", "../assets/textures/dull_metal_albedo.png", true, true);
    m_assetManager.setTexture("metal_spec", "../assets/textures/dull_metal_metallic.png", true, false);
    m_assetManager.setTexture("gold_diff", "../assets/textures/lightgold_albedo.png", false, true);
    m_assetManager.setTexture("gold_spec", "../assets/textures/lightgold_metallic.png", false, false);
    m_assetManager.setTexture("blending", "../assets/textures/blending_transparent_window.png", false, true);
    // skybox maps
    // .........................................................................
    std::vector<std::string> learnopenglFaces {
        "../assets/textures/skybox/right.jpg",
        "../assets/textures/skybox/left.jpg",
        "../assets/textures/skybox/top.jpg",
        "../assets/textures/skybox/bottom.jpg",
        "../assets/textures/skybox/front.jpg",
        "../assets/textures/skybox/back.jpg",
    };
    m_assetManager.setCubemap("learnopengl_skybox", learnopenglFaces, true);

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

    // skybox entity
    // .........................................................................
    SkyboxComponent skyboxSkybox;
    TextureComponent skyboxTexture;
    ShaderProgramComponent skyboxShaderProgram;
    RenderDataComponent skyboxGraphics;
    skyboxTexture.m_cubemap = m_assetManager.getCubemap("learnopengl_skybox");
    skyboxShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("skybox");
    skyboxGraphics.m_vertexCount = cubeMesh.m_vertexCount;
    // setup OpenGL data
    glGenVertexArrays(1, &skyboxGraphics.m_VAO);
    glGenBuffers(1, &skyboxGraphics.m_VBO);
    glBindVertexArray(skyboxGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxMesh.m_verticesSize, skyboxMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glUseProgram(skyboxShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(skyboxShaderProgram.m_shaderProgram, "skybox"), 11);

    // sun entity (pointed down, white light)
    // .........................................................................
    // setup components
    LightComponent sunLight;
    BodyTransformComponent sunTransform;
    ShaderProgramComponent sunShaderProgram;
    LightShaderProgramComponent sunLightShaderProgram;
    RenderDataComponent sunGraphics;
    ShadowFramebufferComponent sunShadow;
    sunLight.m_type = 0;                                   // directional type
    sunLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);   // pointed down
    sunLight.m_ambient = glm::vec3(0.5f, 0.5f, 0.5f);      // white ambient
    sunLight.m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);      // white diffuse
    sunLight.m_specular = glm::vec3(0.5f, 0.5f, 0.5f);     // white specular
    sunShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("light");
    sunLightShaderProgram.m_reflectorProgram = m_assetManager.getShaderProgram("surface");
    sunLightShaderProgram.m_depthMapProgram = m_assetManager.getShaderProgram("shadow_map_depth");
    // configure depth map FBO, create depth texture
    glGenFramebuffers(1, &sunShadow.m_shadowFramebuffer);
    unsigned int sunDepthMap;
    glGenTextures(1, &sunDepthMap);
    glBindTexture(GL_TEXTURE_2D, sunDepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float sunBorderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, sunBorderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, sunShadow.m_shadowFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, sunDepthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // shader configuration
    glUseProgram(sunShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(sunShaderProgram.m_shaderProgram, "diffuseTexture"), 0); 
    glUniform1i(glGetUniformLocation(sunShaderProgram.m_shaderProgram, "shadowMap"), 1); 

    // blueOrb entity (dynamic point source, blue light)
    // .........................................................................
    // setup components
    LightComponent blueOrbLight;
    BodyTransformComponent blueOrbTransform;
    BodyCircleComponent blueOrbCircle;
    ShaderProgramComponent blueOrbShaderProgram;
    LightShaderProgramComponent blueOrbLightShaderProgram;
    RenderDataComponent blueOrbGraphics;
    FixtureUserDataComponent blueOrbUserData;
    ShadowFramebufferComponent blueOrbShadow;
    blueOrbLight.m_type = 1;                                  // point type 
    blueOrbLight.m_scale = glm::vec3(0.5f, 0.5f, 0.5f);       // check Box2D size
    blueOrbLight.m_constant = 1.0f;
    blueOrbLight.m_linear = 0.09f;
    blueOrbLight.m_quadratic = 0.032f;
    blueOrbLight.m_ambient = glm::vec3(0.0f, 0.0f, 1.0f);     // blue ambient
    blueOrbLight.m_diffuse = glm::vec3(0.0f, 0.0f, 1.0f);     // blue diffuse
    blueOrbLight.m_specular = glm::vec3(0.0f, 0.0f, 1.0f);    // blue specular
    blueOrbShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("light");
    blueOrbLightShaderProgram.m_reflectorProgram = m_assetManager.getShaderProgram("surface");
    blueOrbLightShaderProgram.m_depthMapProgram = m_assetManager.getShaderProgram("shadow_map_depth");
    blueOrbGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    blueOrbUserData.m_fixtureType = 0;
    blueOrbCircle.m_bodyDef.type = b2_dynamicBody;
    blueOrbCircle.m_bodyDef.position.Set(-15.0f, 5.0f);
    blueOrbTransform.m_body = m_world->CreateBody(&blueOrbCircle.m_bodyDef);
    blueOrbCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    blueOrbCircle.m_circleShape.m_radius = 0.5f;
    blueOrbCircle.m_fixtureDef.shape = &blueOrbCircle.m_circleShape;
    blueOrbCircle.m_fixtureDef.density = 1.0f;
    blueOrbCircle.m_fixtureDef.friction = 0.3f;
    blueOrbTransform.m_body->CreateFixture(&blueOrbCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &blueOrbGraphics.m_VAO);
    glGenBuffers(1, &blueOrbGraphics.m_VBO);
    glBindVertexArray(blueOrbGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, blueOrbGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // greenOrb entity (dynamic point source, green light)
    // .........................................................................
    // setup components
    LightComponent greenOrbLight;
    BodyTransformComponent greenOrbTransform;
    BodyCircleComponent greenOrbCircle;
    ShaderProgramComponent greenOrbShaderProgram;
    LightShaderProgramComponent greenOrbLightShaderProgram;
    RenderDataComponent greenOrbGraphics;
    FixtureUserDataComponent greenOrbUserData;
    ShadowFramebufferComponent greenOrbShadow;
    greenOrbLight.m_type = 1;                                 // point type
    greenOrbLight.m_scale = glm::vec3(1.5f, 1.5f, 1.5f);      // check Box2D
    greenOrbLight.m_constant = 1.0f;
    greenOrbLight.m_linear = 0.09f;
    greenOrbLight.m_quadratic = 0.032f;
    greenOrbLight.m_ambient = glm::vec3(0.0f, 1.0f, 0.0f);    // green ambient
    greenOrbLight.m_diffuse = glm::vec3(0.0f, 1.0f, 0.0f);    // green diffuse
    greenOrbLight.m_specular = glm::vec3(0.0f, 1.0f, 0.0f);   // green specular
    greenOrbShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("light");
    greenOrbLightShaderProgram.m_reflectorProgram = m_assetManager.getShaderProgram("surface");
    greenOrbLightShaderProgram.m_depthMapProgram = m_assetManager.getShaderProgram("shadow_map_depth");
    greenOrbGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    greenOrbUserData.m_fixtureType = 0;
    greenOrbCircle.m_bodyDef.type = b2_dynamicBody;
    greenOrbCircle.m_bodyDef.position.Set(10.0f, 5.0f);
    greenOrbTransform.m_body = m_world->CreateBody(&greenOrbCircle.m_bodyDef);
    greenOrbCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    greenOrbCircle.m_circleShape.m_radius = 1.5f;
    greenOrbCircle.m_fixtureDef.shape = &greenOrbCircle.m_circleShape;
    greenOrbCircle.m_fixtureDef.density = 1.0f;
    greenOrbCircle.m_fixtureDef.friction = 0.3f;
    greenOrbTransform.m_body->CreateFixture(&greenOrbCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &greenOrbGraphics.m_VAO);
    glGenBuffers(1, &greenOrbGraphics.m_VBO);
    glBindVertexArray(greenOrbGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, greenOrbGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // streetLamp entity (pointed down, yellow light)
    // .........................................................................
    // setup components
    LightComponent streetLampLight;
    BodyTransformComponent streetLampTransform;
    BodyCircleComponent streetLampCircle;
    ShaderProgramComponent streetLampShaderProgram;
    LightShaderProgramComponent streetLampLightShaderProgram;
    RenderDataComponent streetLampGraphics;
    FixtureUserDataComponent streetLampUserData;
    ShadowFramebufferComponent streetLampShadow;
    streetLampLight.m_type = 2;                                    // spot type
    streetLampLight.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);         // check Box2D size
    streetLampLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);    // pointed down
    streetLampLight.m_cutOff = glm::cos(glm::radians(12.5f));
    streetLampLight.m_outerCutOff = glm::cos(glm::radians(15.0f));
    streetLampLight.m_constant = 1.0f;
    streetLampLight.m_linear = 0.09f;
    streetLampLight.m_quadratic = 0.032f;
    streetLampLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);    // no ambient
    streetLampLight.m_diffuse = glm::vec3(1.0f, 1.0f, 0.0f);    // yellow diffuse
    streetLampLight.m_specular = glm::vec3(1.0f, 1.0f, 0.0f);   // yellow specular
    streetLampShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("light");
    streetLampLightShaderProgram.m_reflectorProgram = m_assetManager.getShaderProgram("surface");
    streetLampLightShaderProgram.m_depthMapProgram = m_assetManager.getShaderProgram("shadow_map_depth");
    streetLampGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    streetLampUserData.m_fixtureType = 0;
    streetLampCircle.m_bodyDef.position.Set(-10.0f, 10.0f);
    streetLampTransform.m_body = m_world->CreateBody(&streetLampCircle.m_bodyDef);
    streetLampCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    streetLampCircle.m_circleShape.m_radius = 1.0f;
    streetLampCircle.m_fixtureDef.shape = &streetLampCircle.m_circleShape;
    streetLampCircle.m_fixtureDef.density = 1.0f;
    streetLampCircle.m_fixtureDef.friction = 0.3f;
    streetLampTransform.m_body->CreateFixture(&streetLampCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &streetLampGraphics.m_VAO);
    glGenBuffers(1, &streetLampGraphics.m_VBO);
    glBindVertexArray(streetLampGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, streetLampGraphics.m_VBO);
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
    TextureComponent playerTexture;
    ShaderProgramComponent playerShaderProgram;
    RenderDataComponent playerGraphics;
    FixtureUserDataComponent playerUserData;
    playerMaterial.m_shininess = 128.0f;
    playerTexture.m_diffuse = m_assetManager.getTexture("tiles_diff");
    playerTexture.m_specular = m_assetManager.getTexture("tiles_spec");
    playerShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("surface");
    playerShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    playerGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    playerUserData.m_fixtureType = 2;
    playerCircle.m_bodyDef.type = b2_dynamicBody;
    playerCircle.m_bodyDef.position.Set(0.0f, 5.0f);
    playerTransform.m_body = m_world->CreateBody(&playerCircle.m_bodyDef);
    playerCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    playerCircle.m_circleShape.m_radius = 1.0f;
    playerCircle.m_fixtureDef.shape = &playerCircle.m_circleShape;
    playerCircle.m_fixtureDef.density = 1.0f;
    playerCircle.m_fixtureDef.friction = 0.3f;
    playerCircle.m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&playerUserData);
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
    TextureComponent floorTexture;
    ShaderProgramComponent floorShaderProgram;
    RenderDataComponent floorGraphics;
    FixtureUserDataComponent floorUserData;
    floorMaterial.m_shininess = 32.0f;
    floorTexture.m_diffuse = m_assetManager.getTexture("metal_diff");
    floorTexture.m_specular = m_assetManager.getTexture("metal_spec");
    floorShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("surface");
    floorShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    floorGraphics.m_vertexCount = groundMesh.m_vertexCount;
    // setup Box2D data
    floorUserData.m_fixtureType = 4;
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
    TextureComponent sphereTexture;
    ShaderProgramComponent sphereShaderProgram;
    RenderDataComponent sphereGraphics;
    FixtureUserDataComponent sphereUserData;
    sphereMaterial.m_shininess = 64.0f;
    sphereTexture.m_diffuse = m_assetManager.getTexture("rusted_diff");
    sphereTexture.m_specular = m_assetManager.getTexture("rusted_spec");
    sphereShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("surface");
    sphereShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    sphereGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    sphereUserData.m_fixtureType = 3;
    sphereCircle.m_bodyDef.type = b2_dynamicBody;
    sphereCircle.m_bodyDef.position.Set(-5.0f, 5.0f);
    sphereTransform.m_body = m_world->CreateBody(&sphereCircle.m_bodyDef);
    sphereCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    sphereCircle.m_circleShape.m_radius = 1.0f;
    sphereCircle.m_fixtureDef.shape = &sphereCircle.m_circleShape;
    sphereCircle.m_fixtureDef.density = 1.0f;
    sphereCircle.m_fixtureDef.friction = 0.3f;
    sphereCircle.m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&sphereUserData);
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

    // mirror sphere entity (dynamic, reflecting surface)
    // .........................................................................
    // setup components
    MaterialComponent mirrorMaterial;
    BodyTransformComponent mirrorTransform;
    BodyCircleComponent mirrorCircle;
    TextureComponent mirrorTexture;
    ShaderProgramComponent mirrorShaderProgram;
    RenderDataComponent mirrorGraphics;
    FixtureUserDataComponent mirrorUserData;
    mirrorMaterial.m_shininess = 64.0f;
    mirrorTexture.m_diffuse = m_assetManager.getTexture("gold_diff");
    mirrorTexture.m_specular = m_assetManager.getTexture("gold_spec");
    mirrorShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("surface");
    mirrorShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    mirrorGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    mirrorUserData.m_fixtureType = 3;
    mirrorCircle.m_bodyDef.type = b2_dynamicBody;
    mirrorCircle.m_bodyDef.position.Set(-20.0f, 5.0f);
    mirrorTransform.m_body = m_world->CreateBody(&mirrorCircle.m_bodyDef);
    mirrorCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    mirrorCircle.m_circleShape.m_radius = 1.0f;
    mirrorCircle.m_fixtureDef.shape = &mirrorCircle.m_circleShape;
    mirrorCircle.m_fixtureDef.density = 1.0f;
    mirrorCircle.m_fixtureDef.friction = 0.3f;
    mirrorCircle.m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&mirrorUserData);
    mirrorTransform.m_body->CreateFixture(&mirrorCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &mirrorGraphics.m_VAO);
    glGenBuffers(1, &mirrorGraphics.m_VBO);
    glBindVertexArray(mirrorGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mirrorGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glUseProgram(mirrorShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(mirrorShaderProgram.m_shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(mirrorShaderProgram.m_shaderProgram, "material.specular"), 1);

    // cube entity (dynamic, block-textured cube)
    // .........................................................................
    // setup components
    MaterialComponent cubeMaterial;
    BodyTransformComponent cubeTransform;
    BodyPolygonComponent cubePolygon;
    ShapeSquareComponent cubeShape;
    TextureComponent cubeTexture;
    ShaderProgramComponent cubeShaderProgram;
    RenderDataComponent cubeGraphics;
    FixtureUserDataComponent cubeUserData;
    cubeMaterial.m_shininess = 32.0f;
    cubeTexture.m_diffuse = m_assetManager.getTexture("blocks_diff");
    cubeTexture.m_specular = m_assetManager.getTexture("blocks_spec");
    cubeShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("surface");
    cubeShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    cubeGraphics.m_vertexCount = cubeMesh.m_vertexCount;
    // setup Box2D data
    cubeUserData.m_fixtureType = 4;
    cubePolygon.m_bodyDef.type = b2_dynamicBody;
    cubePolygon.m_bodyDef.position.Set(5.0f, 5.0f);
    cubeTransform.m_body = m_world->CreateBody(&cubePolygon.m_bodyDef);
    cubePolygon.m_polygonShape.Set(cubeShape.m_vertices, cubeShape.m_vertexCount);
    cubePolygon.m_fixtureDef.shape = &cubePolygon.m_polygonShape;
    cubePolygon.m_fixtureDef.density = 1.0f;
    cubePolygon.m_fixtureDef.friction = 0.3f;
    cubePolygon.m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&cubeUserData);
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

    // window entity (flat, blended sprite)
    // .........................................................................
    // setup components
    SpriteComponent windowSprite;
    TextureComponent windowTexture;
    ShaderProgramComponent windowShaderProgram;
    RenderDataComponent windowGraphics;
    windowSprite.m_shininess = 32.0f;
    windowSprite.m_position = glm::vec3(15.0f, 1.0f, 5.0f);
    windowSprite.m_rotation = 0.0f;
    windowSprite.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    windowTexture.m_diffuse = m_assetManager.getTexture("blending");
    windowTexture.m_specular = m_assetManager.getTexture("gold_spec");
    windowShaderProgram.m_shaderProgram = m_assetManager.getShaderProgram("sprite");
    windowShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    windowGraphics.m_vertexCount = spriteMesh.m_vertexCount;
    // setup OpenGL data
    glGenVertexArrays(1, &windowGraphics.m_VAO);
    glGenBuffers(1, &windowGraphics.m_VBO);
    glBindVertexArray(windowGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, windowGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, spriteMesh.m_verticesSize, spriteMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glUseProgram(windowShaderProgram.m_shaderProgram);
    glUniform1i(glGetUniformLocation(windowShaderProgram.m_shaderProgram, "texture1"), 0);


    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // Registry
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto cameraEntity = m_registry.create();
    m_registry.emplace<CameraComponent>(cameraEntity, camera);

    auto skyboxEntity = m_registry.create();
    m_registry.emplace<SkyboxComponent>(skyboxEntity, skyboxSkybox);
    m_registry.emplace<TextureComponent>(skyboxEntity, skyboxTexture);
    m_registry.emplace<ShaderProgramComponent>(skyboxEntity, skyboxShaderProgram);
    m_registry.emplace<RenderDataComponent>(skyboxEntity, skyboxGraphics);

    auto sunEntity = m_registry.create();
    m_registry.emplace<LightComponent>(sunEntity, sunLight);
    m_registry.emplace<BodyTransformComponent>(sunEntity, sunTransform);
    m_registry.emplace<ShaderProgramComponent>(sunEntity, sunShaderProgram);
    m_registry.emplace<LightShaderProgramComponent>(sunEntity, sunLightShaderProgram);
    m_registry.emplace<RenderDataComponent>(sunEntity, sunGraphics);
    m_registry.emplace<ShadowFramebufferComponent>(sunEntity, sunShadow);

    auto blueOrbEntity = m_registry.create();
    m_registry.emplace<LightComponent>(blueOrbEntity, blueOrbLight);
    m_registry.emplace<BodyTransformComponent>(blueOrbEntity, blueOrbTransform);
    m_registry.emplace<ShaderProgramComponent>(blueOrbEntity, blueOrbShaderProgram);
    m_registry.emplace<LightShaderProgramComponent>(blueOrbEntity, blueOrbLightShaderProgram);
    m_registry.emplace<RenderDataComponent>(blueOrbEntity, blueOrbGraphics);
    m_registry.emplace<FixtureUserDataComponent>(blueOrbEntity, blueOrbUserData);
    m_registry.emplace<ShadowFramebufferComponent>(blueOrbEntity, blueOrbShadow);
    blueOrbUserData.m_enttEntity = &blueOrbEntity;

    auto greenOrbEntity = m_registry.create();
    m_registry.emplace<LightComponent>(greenOrbEntity, greenOrbLight);
    m_registry.emplace<BodyTransformComponent>(greenOrbEntity, greenOrbTransform);
    m_registry.emplace<ShaderProgramComponent>(greenOrbEntity, greenOrbShaderProgram);
    m_registry.emplace<LightShaderProgramComponent>(greenOrbEntity, greenOrbLightShaderProgram);
    m_registry.emplace<RenderDataComponent>(greenOrbEntity, greenOrbGraphics);
    m_registry.emplace<FixtureUserDataComponent>(greenOrbEntity, greenOrbUserData);
    m_registry.emplace<ShadowFramebufferComponent>(greenOrbEntity, greenOrbShadow);
    greenOrbUserData.m_enttEntity = &greenOrbEntity;

    auto streetLampEntity = m_registry.create();
    m_registry.emplace<LightComponent>(streetLampEntity, streetLampLight);
    m_registry.emplace<BodyTransformComponent>(streetLampEntity, streetLampTransform);
    m_registry.emplace<BodyCircleComponent>(streetLampEntity, streetLampCircle);
    m_registry.emplace<ShaderProgramComponent>(streetLampEntity, streetLampShaderProgram);
    m_registry.emplace<LightShaderProgramComponent>(streetLampEntity, streetLampLightShaderProgram);
    m_registry.emplace<RenderDataComponent>(streetLampEntity, streetLampGraphics);
    m_registry.emplace<FixtureUserDataComponent>(streetLampEntity, streetLampUserData);
    m_registry.emplace<ShadowFramebufferComponent>(streetLampEntity, streetLampShadow);
    streetLampUserData.m_enttEntity = &streetLampEntity;

    auto playerEntity = m_registry.create();
    m_registry.emplace<PlayerComponent>(playerEntity, playerPlayer);
    m_registry.emplace<MaterialComponent>(playerEntity, playerMaterial);
    m_registry.emplace<BodyTransformComponent>(playerEntity, playerTransform);
    m_registry.emplace<TextureComponent>(playerEntity, playerTexture);
    m_registry.emplace<ShaderProgramComponent>(playerEntity, playerShaderProgram);
    m_registry.emplace<RenderDataComponent>(playerEntity, playerGraphics);
    m_registry.emplace<FixtureUserDataComponent>(playerEntity, playerUserData);
    playerUserData.m_enttEntity = &playerEntity;

    auto floorEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(floorEntity, floorMaterial);
    m_registry.emplace<BodyTransformComponent>(floorEntity, floorTransform);
    m_registry.emplace<TextureComponent>(floorEntity, floorTexture);
    m_registry.emplace<ShaderProgramComponent>(floorEntity, floorShaderProgram);
    m_registry.emplace<RenderDataComponent>(floorEntity, floorGraphics);
    m_registry.emplace<FixtureUserDataComponent>(floorEntity, floorUserData);
    floorUserData.m_enttEntity = &floorEntity;

    auto sphereEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(sphereEntity, sphereMaterial);
    m_registry.emplace<BodyTransformComponent>(sphereEntity, sphereTransform);
    m_registry.emplace<TextureComponent>(sphereEntity, sphereTexture);
    m_registry.emplace<ShaderProgramComponent>(sphereEntity, sphereShaderProgram);
    m_registry.emplace<RenderDataComponent>(sphereEntity, sphereGraphics);
    m_registry.emplace<FixtureUserDataComponent>(sphereEntity, sphereUserData);
    sphereUserData.m_enttEntity = &sphereEntity;

    auto mirrorEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(mirrorEntity, mirrorMaterial);
    m_registry.emplace<BodyTransformComponent>(mirrorEntity, mirrorTransform);
    m_registry.emplace<TextureComponent>(mirrorEntity, mirrorTexture);
    m_registry.emplace<ShaderProgramComponent>(mirrorEntity, mirrorShaderProgram);
    m_registry.emplace<RenderDataComponent>(mirrorEntity, mirrorGraphics);
    m_registry.emplace<FixtureUserDataComponent>(mirrorEntity, mirrorUserData);
    mirrorUserData.m_enttEntity = &mirrorEntity;

    auto cubeEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(cubeEntity, cubeMaterial);
    m_registry.emplace<BodyTransformComponent>(cubeEntity, cubeTransform);
    m_registry.emplace<TextureComponent>(cubeEntity, cubeTexture);
    m_registry.emplace<ShaderProgramComponent>(cubeEntity, cubeShaderProgram);
    m_registry.emplace<RenderDataComponent>(cubeEntity, cubeGraphics);
    m_registry.emplace<FixtureUserDataComponent>(cubeEntity, cubeUserData);
    cubeUserData.m_enttEntity = &cubeEntity;

    auto windowEntity = m_registry.create();
    m_registry.emplace<SpriteComponent>(windowEntity, windowSprite);
    m_registry.emplace<TextureComponent>(windowEntity, windowTexture);
    m_registry.emplace<ShaderProgramComponent>(windowEntity, windowShaderProgram);
    m_registry.emplace<RenderDataComponent>(windowEntity, windowGraphics);
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

    m_renderSystem.update(renderFactor, m_registry);

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