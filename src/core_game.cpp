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
    m_assetManager.setVShader("solid_color_vert", "../assets/shaders/solid_color.vert");
    m_assetManager.setFShader("solid_color_frag", "../assets/shaders/solid_color.frag");
    m_assetManager.setVShader("stencil_vert", "../assets/shaders/stencil.vert");
    m_assetManager.setFShader("stencil_frag", "../assets/shaders/stencil.frag");
    m_assetManager.setVShader("sprite_vert", "../assets/shaders/sprite.vert");
    m_assetManager.setFShader("sprite_frag", "../assets/shaders/sprite.frag");
    m_assetManager.setVShader("skybox_vert", "../assets/shaders/skybox.vert");
    m_assetManager.setFShader("skybox_frag", "../assets/shaders/skybox.frag");
    m_assetManager.setVShader("shadow_depth_vert", "../assets/shaders/shadow_depth.vert");
    m_assetManager.setFShader("shadow_depth_frag", "../assets/shaders/shadow_depth.frag");
    m_assetManager.setVShader("shadow_depth_cube_vert", "../assets/shaders/shadow_depth_cube.vert");
    m_assetManager.setGShader("shadow_depth_cube_geom", "../assets/shaders/shadow_depth_cube.geom");
    m_assetManager.setFShader("shadow_depth_cube_frag", "../assets/shaders/shadow_depth_cube.frag");
    m_assetManager.setVShader("shadow_render_vert", "../assets/shaders/shadow_render.vert");
    m_assetManager.setFShader("shadow_render_frag", "../assets/shaders/shadow_render.frag");
    m_assetManager.setVShader("basic_lighting_vert", "../assets/shaders/basic_lighting.vert");
    m_assetManager.setFShader("basic_lighting_frag", "../assets/shaders/basic_lighting.frag");
    m_assetManager.setVShader("shadow_framebuffer_vert", "../assets/shaders/shadow_framebuffer.vert");
    m_assetManager.setFShader("shadow_framebuffer_frag", "../assets/shaders/shadow_framebuffer.frag");

    // shader programs
    // .........................................................................
    unsigned int vertex, fragment, geometry;
    vertex = m_assetManager.getVShader("solid_color_vert");
    fragment = m_assetManager.getFShader("solid_color_frag");
    m_assetManager.setShaderProgram("solid_color", vertex, fragment);
    vertex = m_assetManager.getVShader("stencil_vert");
    fragment = m_assetManager.getFShader("stencil_frag");
    m_assetManager.setShaderProgram("stencil", vertex, fragment);
    vertex = m_assetManager.getVShader("sprite_vert");
    fragment = m_assetManager.getFShader("sprite_frag");
    m_assetManager.setShaderProgram("sprite", vertex, fragment);
    vertex = m_assetManager.getVShader("skybox_vert");
    fragment = m_assetManager.getFShader("skybox_frag");
    m_assetManager.setShaderProgram("skybox", vertex, fragment);
    vertex = m_assetManager.getVShader("shadow_depth_vert");
    fragment = m_assetManager.getFShader("shadow_depth_frag");
    m_assetManager.setShaderProgram("shadow_depth", vertex, fragment);
    vertex = m_assetManager.getVShader("shadow_depth_cube_vert");
    geometry = m_assetManager.getGShader("shadow_depth_cube_geom");
    fragment = m_assetManager.getFShader("shadow_depth_cube_frag");
    m_assetManager.setShaderProgram("shadow_depth_cube", vertex, geometry, fragment);
    vertex = m_assetManager.getVShader("shadow_render_vert");
    fragment = m_assetManager.getFShader("shadow_render_frag");
    m_assetManager.setShaderProgram("shadow_render", vertex, fragment);
    vertex = m_assetManager.getVShader("basic_lighting_vert");
    fragment = m_assetManager.getFShader("basic_lighting_frag");
    m_assetManager.setShaderProgram("basic_lighting", vertex, fragment);
    vertex = m_assetManager.getVShader("shadow_framebuffer_vert");
    fragment = m_assetManager.getFShader("shadow_framebuffer_frag");
    m_assetManager.setShaderProgram("shadow_framebuffer", vertex, fragment);

    // shader configuration
    // .........................................................................
    glUseProgram(m_assetManager.getShaderProgram("sprite"));
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("sprite"), "texture1"), 0);
    glUseProgram(m_assetManager.getShaderProgram("shadow_render"));
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("shadow_render"), "diffuseTexture"), 0); 
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("shadow_render"), "shadowMap"), 1); 
    glUseProgram(m_assetManager.getShaderProgram("basic_lighting"));
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "material.diffuse"), 0); 
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "material.specular"), 1);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "spotLights[0].depthTex"), 2);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "spotLights[1].depthTex"), 3);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "spotLights[2].depthTex"), 4);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "pointLights[0].depthCube"), 5);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "pointLights[1].depthCube"), 6);
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("basic_lighting"), "pointLights[2].depthCube"), 7);
    glUseProgram(m_assetManager.getShaderProgram("shadow_framebuffer"));
    glUniform1i(glGetUniformLocation(m_assetManager.getShaderProgram("shadow_framebuffer"), "depthMap"), 0); 
    glUniform1f(glGetUniformLocation(m_assetManager.getShaderProgram("shadow_framebuffer"), "near_plane"), 1.0f);
    glUniform1f(glGetUniformLocation(m_assetManager.getShaderProgram("shadow_framebuffer"), "far_plane"), 15.0f);

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
    m_assetManager.setTexture("white", "../assets/textures/white.jpg", true, true);

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
    skyboxShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("skybox");
    skyboxGraphics.m_vertexCount = cubeMesh.m_vertexCount;
    // setup OpenGL data
    glGenVertexArrays(1, &skyboxGraphics.m_VAO);
    glGenBuffers(1, &skyboxGraphics.m_VBO);
    glBindVertexArray(skyboxGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxMesh.m_verticesSize, skyboxMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glUseProgram(skyboxShaderProgram.m_outputProgram);
    glUniform1i(glGetUniformLocation(skyboxShaderProgram.m_outputProgram, "skybox"), 11);

    // sun entity (pointed down, white light)
    // .........................................................................
    // setup components
    LightComponent sunLight;
    BodyTransformComponent sunTransform;
    ShaderProgramComponent sunShaderProgram;
    RenderDataComponent sunGraphics;
    ShadowFramebufferComponent sunShadow;
    sunLight.m_type = 0;                                   // directional type
    sunLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);   // pointed down
    sunLight.m_ambient = glm::vec3(0.15f, 0.15f, 0.15f);      // white ambient
    sunLight.m_diffuse = glm::vec3(0.15f, 0.15f, 0.15f);      // white diffuse
    sunLight.m_specular = glm::vec3(0.15f, 0.15f, 0.15f);     // white specular
    sunShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    // setup shadow mapping
    sunShadow.m_type = 0; // no shadow casting

    // redOrb entity (dynamic point source, red light)
    // .........................................................................
    // setup components
    LightComponent redOrbLight;
    BodyTransformComponent redOrbTransform;
    BodyCircleComponent redOrbCircle;
    ShaderProgramComponent redOrbShaderProgram;
    RenderDataComponent redOrbGraphics;
    FixtureUserDataComponent redOrbUserData;
    ShadowFramebufferComponent redOrbShadow;
    redOrbLight.m_type = 1;                                  // point type 
    redOrbLight.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);       // check Box2D size
    redOrbLight.m_constant = 1.0f;
    redOrbLight.m_linear = 0.14f;
    redOrbLight.m_quadratic = 0.07f;
    redOrbLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);     // red ambient
    redOrbLight.m_diffuse = glm::vec3(1.0f, 0.0f, 0.0f);     // red diffuse
    redOrbLight.m_specular = glm::vec3(1.0f, 0.0f, 0.0f);    // red specular
    redOrbShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    redOrbShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    redOrbShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth_cube");
    redOrbGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    redOrbUserData.m_fixtureType = 0;
    redOrbCircle.m_bodyDef.type = b2_dynamicBody;
    redOrbCircle.m_bodyDef.position.Set(10.0f, 5.0f);
    redOrbTransform.m_body = m_world->CreateBody(&redOrbCircle.m_bodyDef);
    redOrbCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    redOrbCircle.m_circleShape.m_radius = 1.0f;
    redOrbCircle.m_fixtureDef.shape = &redOrbCircle.m_circleShape;
    redOrbCircle.m_fixtureDef.density = 1.0f;
    redOrbCircle.m_fixtureDef.friction = 0.3f;
    redOrbTransform.m_body->CreateFixture(&redOrbCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &redOrbGraphics.m_VAO);
    glGenBuffers(1, &redOrbGraphics.m_VBO);
    glBindVertexArray(redOrbGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, redOrbGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // setup shadow mapping
    redOrbShadow.m_type = 2; // omnidirectional shadow casting
    redOrbShadow.m_index = 0;
    redOrbShadow.m_nearPlane = 1.0f;
    redOrbShadow.m_farPlane = 32.0f;
    glGenFramebuffers(1, &redOrbShadow.m_shadowFramebuffer);
    glGenTextures(1, &redOrbShadow.m_depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, redOrbShadow.m_depthCubemap);
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, redOrbShadow.m_shadowFramebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, redOrbShadow.m_depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // greenOrb entity (dynamic point source, green light)
    // .........................................................................
    // setup components
    LightComponent greenOrbLight;
    BodyTransformComponent greenOrbTransform;
    BodyCircleComponent greenOrbCircle;
    ShaderProgramComponent greenOrbShaderProgram;
    RenderDataComponent greenOrbGraphics;
    FixtureUserDataComponent greenOrbUserData;
    ShadowFramebufferComponent greenOrbShadow;
    greenOrbLight.m_type = 1;                                 // point type
    greenOrbLight.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);      // check Box2D
    greenOrbLight.m_constant = 1.0f;
    greenOrbLight.m_linear = 0.14f;
    greenOrbLight.m_quadratic = 0.07f;
    greenOrbLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);    // green ambient
    greenOrbLight.m_diffuse = glm::vec3(0.0f, 1.0f, 0.0f);    // green diffuse
    greenOrbLight.m_specular = glm::vec3(0.0f, 1.0f, 0.0f);   // green specular
    greenOrbShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    greenOrbShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    greenOrbShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth_cube");
    greenOrbGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    greenOrbUserData.m_fixtureType = 0;
    greenOrbCircle.m_bodyDef.type = b2_dynamicBody;
    greenOrbCircle.m_bodyDef.position.Set(25.0f, 5.0f);
    greenOrbTransform.m_body = m_world->CreateBody(&greenOrbCircle.m_bodyDef);
    greenOrbCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    greenOrbCircle.m_circleShape.m_radius = 1.0f;
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
    // setup shadow mapping
    greenOrbShadow.m_type = 2; // omnidirectional shadow casting
    greenOrbShadow.m_index = 1;
    greenOrbShadow.m_nearPlane = 1.0f;
    greenOrbShadow.m_farPlane = 32.0f;
    glGenFramebuffers(1, &greenOrbShadow.m_shadowFramebuffer);
    glGenTextures(1, &greenOrbShadow.m_depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, greenOrbShadow.m_depthCubemap);
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, greenOrbShadow.m_shadowFramebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, greenOrbShadow.m_depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // blueOrb entity (dynamic point source, blue light)
    // .........................................................................
    // setup components
    LightComponent blueOrbLight;
    BodyTransformComponent blueOrbTransform;
    BodyCircleComponent blueOrbCircle;
    ShaderProgramComponent blueOrbShaderProgram;
    RenderDataComponent blueOrbGraphics;
    FixtureUserDataComponent blueOrbUserData;
    ShadowFramebufferComponent blueOrbShadow;
    blueOrbLight.m_type = 1;                                  // point type 
    blueOrbLight.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);       // check Box2D size
    blueOrbLight.m_constant = 1.0f;
    blueOrbLight.m_linear = 0.14f;
    blueOrbLight.m_quadratic = 0.07f;
    blueOrbLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);     // blue ambient
    blueOrbLight.m_diffuse = glm::vec3(0.0f, 0.0f, 1.0f);     // blue diffuse
    blueOrbLight.m_specular = glm::vec3(0.0f, 0.0f, 1.0f);    // blue specular
    blueOrbShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    blueOrbShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    blueOrbShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth_cube");
    blueOrbGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    blueOrbUserData.m_fixtureType = 0;
    blueOrbCircle.m_bodyDef.type = b2_dynamicBody;
    blueOrbCircle.m_bodyDef.position.Set(-15.0f, 5.0f);
    blueOrbTransform.m_body = m_world->CreateBody(&blueOrbCircle.m_bodyDef);
    blueOrbCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    blueOrbCircle.m_circleShape.m_radius = 1.0f;
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
    // setup shadow mapping
    blueOrbShadow.m_type = 2; // omnidirectional shadow casting
    blueOrbShadow.m_index = 2;
    blueOrbShadow.m_nearPlane = 1.0f;
    blueOrbShadow.m_farPlane = 32.0f;
    glGenFramebuffers(1, &blueOrbShadow.m_shadowFramebuffer);
    glGenTextures(1, &blueOrbShadow.m_depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, blueOrbShadow.m_depthCubemap);
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, blueOrbShadow.m_shadowFramebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, blueOrbShadow.m_depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // yellowLamp entity (fixed position, pointed down, yellow light)
    // .........................................................................
    // setup components
    LightComponent yellowLampLight;
    BodyTransformComponent yellowLampTransform;
    BodyCircleComponent yellowLampCircle;
    ShaderProgramComponent yellowLampShaderProgram;
    RenderDataComponent yellowLampGraphics;
    FixtureUserDataComponent yellowLampUserData;
    ShadowFramebufferComponent yellowLampShadow;
    yellowLampLight.m_type = 2;                                    // spot type
    yellowLampLight.m_scale = glm::vec3(1.0f, 1.0f, 1.0f);         // check Box2D size
    yellowLampLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);    // pointed down
    yellowLampLight.m_cutOff = glm::cos(glm::radians(15.0f));
    yellowLampLight.m_outerCutOff = glm::cos(glm::radians(17.5f));
    yellowLampLight.m_constant = 1.0f;
    yellowLampLight.m_linear = 0.09f;
    yellowLampLight.m_quadratic = 0.032f;
    yellowLampLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);    // no ambient
    yellowLampLight.m_diffuse = glm::vec3(1.0f, 1.0f, 0.0f);    // yellow diffuse
    yellowLampLight.m_specular = glm::vec3(1.0f, 1.0f, 0.0f);   // yellow specular
    yellowLampShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    yellowLampShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    yellowLampShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth");
    yellowLampGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    yellowLampUserData.m_fixtureType = 0;
    yellowLampCircle.m_bodyDef.position.Set(-10.0f, 10.0f);
    yellowLampTransform.m_body = m_world->CreateBody(&yellowLampCircle.m_bodyDef);
    yellowLampCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    yellowLampCircle.m_circleShape.m_radius = 1.0f;
    yellowLampCircle.m_fixtureDef.shape = &yellowLampCircle.m_circleShape;
    yellowLampCircle.m_fixtureDef.density = 1.0f;
    yellowLampCircle.m_fixtureDef.friction = 0.3f;
    yellowLampTransform.m_body->CreateFixture(&yellowLampCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &yellowLampGraphics.m_VAO);
    glGenBuffers(1, &yellowLampGraphics.m_VBO);
    glBindVertexArray(yellowLampGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, yellowLampGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // setup shadow mapping
    yellowLampShadow.m_type = 1; // mono-directional shadow casting
    yellowLampShadow.m_index = 0;
    yellowLampShadow.m_nearPlane = 1.0f;
    yellowLampShadow.m_farPlane = 15.0f;
    glGenFramebuffers(1, &yellowLampShadow.m_shadowFramebuffer);
    glGenTextures(1, &yellowLampShadow.m_depthMap);
    glBindTexture(GL_TEXTURE_2D, yellowLampShadow.m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float yellowLampBorderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, yellowLampBorderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, yellowLampShadow.m_shadowFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, yellowLampShadow.m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // magentaLamp entity (fixed position, pointed down, magenta light)
    // .........................................................................
    // setup components
    LightComponent magentaLampLight;
    BodyTransformComponent magentaLampTransform;
    BodyCircleComponent magentaLampCircle;
    ShaderProgramComponent magentaLampShaderProgram;
    RenderDataComponent magentaLampGraphics;
    FixtureUserDataComponent magentaLampUserData;
    ShadowFramebufferComponent magentaLampShadow;
    magentaLampLight.m_type = 2;                                    // spot type
    magentaLampLight.m_scale = glm::vec3(1.25f, 1.25f, 1.25f);      // check Box2D size
    magentaLampLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);    // pointed down
    magentaLampLight.m_cutOff = glm::cos(glm::radians(15.0f));
    magentaLampLight.m_outerCutOff = glm::cos(glm::radians(17.5f));
    magentaLampLight.m_constant = 1.0f;
    magentaLampLight.m_linear = 0.09f;
    magentaLampLight.m_quadratic = 0.032f;
    magentaLampLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);    // no ambient
    magentaLampLight.m_diffuse = glm::vec3(1.0f, 0.0f, 1.0f);    // magenta diffuse
    magentaLampLight.m_specular = glm::vec3(1.0f, 0.0f, 1.0f);   // magenta specular
    magentaLampShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    magentaLampShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    magentaLampShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth");
    magentaLampGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    magentaLampUserData.m_fixtureType = 0;
    magentaLampCircle.m_bodyDef.position.Set(-25.0f, 10.0f);
    magentaLampTransform.m_body = m_world->CreateBody(&magentaLampCircle.m_bodyDef);
    magentaLampCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    magentaLampCircle.m_circleShape.m_radius = 1.25f;
    magentaLampCircle.m_fixtureDef.shape = &magentaLampCircle.m_circleShape;
    magentaLampCircle.m_fixtureDef.density = 1.0f;
    magentaLampCircle.m_fixtureDef.friction = 0.3f;
    magentaLampTransform.m_body->CreateFixture(&magentaLampCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &magentaLampGraphics.m_VAO);
    glGenBuffers(1, &magentaLampGraphics.m_VBO);
    glBindVertexArray(magentaLampGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, magentaLampGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // setup shadow mapping
    magentaLampShadow.m_type = 1; // monodirectional shadow casting
    magentaLampShadow.m_index = 1;
    magentaLampShadow.m_nearPlane = 1.0f;
    magentaLampShadow.m_farPlane = 15.0f;
    glGenFramebuffers(1, &magentaLampShadow.m_shadowFramebuffer);
    glGenTextures(1, &magentaLampShadow.m_depthMap);
    glBindTexture(GL_TEXTURE_2D, magentaLampShadow.m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float magentaLampBorderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, magentaLampBorderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, magentaLampShadow.m_shadowFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, magentaLampShadow.m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // cyanLamp entity (fixed position, pointed down, cyan light)
    // .........................................................................
    // setup components
    LightComponent cyanLampLight;
    BodyTransformComponent cyanLampTransform;
    BodyCircleComponent cyanLampCircle;
    ShaderProgramComponent cyanLampShaderProgram;
    RenderDataComponent cyanLampGraphics;
    FixtureUserDataComponent cyanLampUserData;
    ShadowFramebufferComponent cyanLampShadow;
    cyanLampLight.m_type = 2;                                    // spot type
    cyanLampLight.m_scale = glm::vec3(0.75f, 0.75f, 0.75f);      // check Box2D size
    cyanLampLight.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);    // pointed down
    cyanLampLight.m_cutOff = glm::cos(glm::radians(15.0f));
    cyanLampLight.m_outerCutOff = glm::cos(glm::radians(17.5f));
    cyanLampLight.m_constant = 1.0f;
    cyanLampLight.m_linear = 0.09f;
    cyanLampLight.m_quadratic = 0.032f;
    cyanLampLight.m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);    // no ambient
    cyanLampLight.m_diffuse = glm::vec3(0.0f, 1.0f, 1.0f);    // cyan diffuse
    cyanLampLight.m_specular = glm::vec3(0.0f, 1.0f, 1.0f);   // cyan specular
    cyanLampShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("solid_color");
    cyanLampShaderProgram.m_lightProgram = m_assetManager.getShaderProgram("basic_lighting");
    cyanLampShaderProgram.m_shadowProgram = m_assetManager.getShaderProgram("shadow_depth");
    cyanLampGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    cyanLampUserData.m_fixtureType = 0;
    cyanLampCircle.m_bodyDef.position.Set(20.0f, 10.0f);
    cyanLampTransform.m_body = m_world->CreateBody(&cyanLampCircle.m_bodyDef);
    cyanLampCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    cyanLampCircle.m_circleShape.m_radius = 0.75f;
    cyanLampCircle.m_fixtureDef.shape = &cyanLampCircle.m_circleShape;
    cyanLampCircle.m_fixtureDef.density = 1.0f;
    cyanLampCircle.m_fixtureDef.friction = 0.3f;
    cyanLampTransform.m_body->CreateFixture(&cyanLampCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &cyanLampGraphics.m_VAO);
    glGenBuffers(1, &cyanLampGraphics.m_VBO);
    glBindVertexArray(cyanLampGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cyanLampGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // setup shadow mapping
    cyanLampShadow.m_type = 1; // monodirectional shadow casting
    cyanLampShadow.m_index = 2;
    cyanLampShadow.m_nearPlane = 1.0f;
    cyanLampShadow.m_farPlane = 15.0f;
    glGenFramebuffers(1, &cyanLampShadow.m_shadowFramebuffer);
    glGenTextures(1, &cyanLampShadow.m_depthMap);
    glBindTexture(GL_TEXTURE_2D, cyanLampShadow.m_depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float cyanLampBorderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, cyanLampBorderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, cyanLampShadow.m_shadowFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, cyanLampShadow.m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
    playerShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("basic_lighting");
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
    floorShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("basic_lighting");
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
    sphereMaterial.m_shininess = 32.0f;
    sphereTexture.m_diffuse = m_assetManager.getTexture("rusted_diff");
    sphereTexture.m_specular = m_assetManager.getTexture("rusted_spec");
    sphereShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("basic_lighting");
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

    // gold sphere entity (dynamic, reflecting surface)
    // .........................................................................
    // setup components
    MaterialComponent goldMaterial;
    BodyTransformComponent goldTransform;
    BodyCircleComponent goldCircle;
    TextureComponent goldTexture;
    ShaderProgramComponent goldShaderProgram;
    RenderDataComponent goldGraphics;
    FixtureUserDataComponent goldUserData;
    goldMaterial.m_shininess = 256.0f;
    goldTexture.m_diffuse = m_assetManager.getTexture("gold_diff");
    goldTexture.m_specular = m_assetManager.getTexture("gold_spec");
    goldShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("basic_lighting");
    goldShaderProgram.m_stencilProgram = m_assetManager.getShaderProgram("stencil");
    goldGraphics.m_vertexCount = sphereMesh.m_vertexCount;
    // setup Box2D data
    goldUserData.m_fixtureType = 3;
    goldCircle.m_bodyDef.type = b2_dynamicBody;
    goldCircle.m_bodyDef.position.Set(-20.0f, 5.0f);
    goldTransform.m_body = m_world->CreateBody(&goldCircle.m_bodyDef);
    goldCircle.m_circleShape.m_p.Set(0.0f, 0.0f);
    goldCircle.m_circleShape.m_radius = 1.0f;
    goldCircle.m_fixtureDef.shape = &goldCircle.m_circleShape;
    goldCircle.m_fixtureDef.density = 1.0f;
    goldCircle.m_fixtureDef.friction = 0.3f;
    goldCircle.m_fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&goldUserData);
    goldTransform.m_body->CreateFixture(&goldCircle.m_fixtureDef);
    // setup OpenGL data
    glGenVertexArrays(1, &goldGraphics.m_VAO);
    glGenBuffers(1, &goldGraphics.m_VBO);
    glBindVertexArray(goldGraphics.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, goldGraphics.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereMesh.m_verticesSize, sphereMesh.m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
    cubeShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("basic_lighting");
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
    windowShaderProgram.m_outputProgram = m_assetManager.getShaderProgram("sprite");
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
    m_registry.emplace<RenderDataComponent>(sunEntity, sunGraphics);
    m_registry.emplace<ShadowFramebufferComponent>(sunEntity, sunShadow);

    auto redOrbEntity = m_registry.create();
    m_registry.emplace<LightComponent>(redOrbEntity, redOrbLight);
    m_registry.emplace<BodyTransformComponent>(redOrbEntity, redOrbTransform);
    m_registry.emplace<ShaderProgramComponent>(redOrbEntity, redOrbShaderProgram);
    m_registry.emplace<RenderDataComponent>(redOrbEntity, redOrbGraphics);
    m_registry.emplace<FixtureUserDataComponent>(redOrbEntity, redOrbUserData);
    m_registry.emplace<ShadowFramebufferComponent>(redOrbEntity, redOrbShadow);
    redOrbUserData.m_enttEntity = &redOrbEntity;

    auto greenOrbEntity = m_registry.create();
    m_registry.emplace<LightComponent>(greenOrbEntity, greenOrbLight);
    m_registry.emplace<BodyTransformComponent>(greenOrbEntity, greenOrbTransform);
    m_registry.emplace<ShaderProgramComponent>(greenOrbEntity, greenOrbShaderProgram);
    m_registry.emplace<RenderDataComponent>(greenOrbEntity, greenOrbGraphics);
    m_registry.emplace<FixtureUserDataComponent>(greenOrbEntity, greenOrbUserData);
    m_registry.emplace<ShadowFramebufferComponent>(greenOrbEntity, greenOrbShadow);
    greenOrbUserData.m_enttEntity = &greenOrbEntity;

    auto blueOrbEntity = m_registry.create();
    m_registry.emplace<LightComponent>(blueOrbEntity, blueOrbLight);
    m_registry.emplace<BodyTransformComponent>(blueOrbEntity, blueOrbTransform);
    m_registry.emplace<ShaderProgramComponent>(blueOrbEntity, blueOrbShaderProgram);
    m_registry.emplace<RenderDataComponent>(blueOrbEntity, blueOrbGraphics);
    m_registry.emplace<FixtureUserDataComponent>(blueOrbEntity, blueOrbUserData);
    m_registry.emplace<ShadowFramebufferComponent>(blueOrbEntity, blueOrbShadow);
    blueOrbUserData.m_enttEntity = &blueOrbEntity;

    auto yellowLampEntity = m_registry.create();
    m_registry.emplace<LightComponent>(yellowLampEntity, yellowLampLight);
    m_registry.emplace<BodyTransformComponent>(yellowLampEntity, yellowLampTransform);
    m_registry.emplace<BodyCircleComponent>(yellowLampEntity, yellowLampCircle);
    m_registry.emplace<ShaderProgramComponent>(yellowLampEntity, yellowLampShaderProgram);
    m_registry.emplace<RenderDataComponent>(yellowLampEntity, yellowLampGraphics);
    m_registry.emplace<FixtureUserDataComponent>(yellowLampEntity, yellowLampUserData);
    m_registry.emplace<ShadowFramebufferComponent>(yellowLampEntity, yellowLampShadow);
    yellowLampUserData.m_enttEntity = &yellowLampEntity;

    auto magentaLampEntity = m_registry.create();
    m_registry.emplace<LightComponent>(magentaLampEntity, magentaLampLight);
    m_registry.emplace<BodyTransformComponent>(magentaLampEntity, magentaLampTransform);
    m_registry.emplace<BodyCircleComponent>(magentaLampEntity, magentaLampCircle);
    m_registry.emplace<ShaderProgramComponent>(magentaLampEntity, magentaLampShaderProgram);
    m_registry.emplace<RenderDataComponent>(magentaLampEntity, magentaLampGraphics);
    m_registry.emplace<FixtureUserDataComponent>(magentaLampEntity, magentaLampUserData);
    m_registry.emplace<ShadowFramebufferComponent>(magentaLampEntity, magentaLampShadow);
    magentaLampUserData.m_enttEntity = &magentaLampEntity;

    auto cyanLampEntity = m_registry.create();
    m_registry.emplace<LightComponent>(cyanLampEntity, cyanLampLight);
    m_registry.emplace<BodyTransformComponent>(cyanLampEntity, cyanLampTransform);
    m_registry.emplace<BodyCircleComponent>(cyanLampEntity, cyanLampCircle);
    m_registry.emplace<ShaderProgramComponent>(cyanLampEntity, cyanLampShaderProgram);
    m_registry.emplace<RenderDataComponent>(cyanLampEntity, cyanLampGraphics);
    m_registry.emplace<FixtureUserDataComponent>(cyanLampEntity, cyanLampUserData);
    m_registry.emplace<ShadowFramebufferComponent>(cyanLampEntity, cyanLampShadow);
    cyanLampUserData.m_enttEntity = &cyanLampEntity;

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

    auto goldEntity = m_registry.create();
    m_registry.emplace<MaterialComponent>(goldEntity, goldMaterial);
    m_registry.emplace<BodyTransformComponent>(goldEntity, goldTransform);
    m_registry.emplace<TextureComponent>(goldEntity, goldTexture);
    m_registry.emplace<ShaderProgramComponent>(goldEntity, goldShaderProgram);
    m_registry.emplace<RenderDataComponent>(goldEntity, goldGraphics);
    m_registry.emplace<FixtureUserDataComponent>(goldEntity, goldUserData);
    goldUserData.m_enttEntity = &goldEntity;

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