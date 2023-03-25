// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.cpp
//  implementation of Render System 
// -----------------------------------------------------------------------------

#include "system_render.h"

//      1) store camera data
//      2) store shadow map data for point/spot lights
//      3) store reflection data for directional/point/spot, render point/spot
//      4) render skybox
//      5) render gameplay entities
//      6) render sprites
//      7) render text
//      8) render stencil outlines

void RenderSystem::update(
    const float timeStep, 
    entt::registry& registry
) {
    unsigned int shadowTextures[3];
    unsigned int shadowCubes[3];
    int framebufferWidth;
    int framebufferHeight;
    glfwGetFramebufferSize(m_glfwWindow, &framebufferWidth, &framebufferHeight);

    auto gameplayEntities = registry.view<
        MaterialComponent,
        BodyTransformComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 1) store camera entity data
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // camera data
    float cameraZoom;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    auto cameraEntities = registry.view<CameraComponent>();
    cameraEntities.each([&](const auto& camera) {
        // if 'first' camera (designates main camera)
        if (camera.m_type == 1) {
            cameraZoom = camera.m_zoom;
            cameraPosition = camera.m_position;
            cameraFront = camera.m_front;
            cameraUp = camera.m_up;
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 2) shadow mapping
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto lightEntities = registry.view<
        LightComponent,
        BodyTransformComponent,
        ShaderProgramComponent,
        RenderDataComponent,
        ShadowFramebufferComponent
    >();
    lightEntities.each([&](
        const auto& rootLight,
        const auto& rootBody,
        const auto& rootShader,
        const auto& rootGraphics,
        const auto& rootShadow
    ) {
        // .................................................................
        // spotlight: monodirectional shadow mapping
        // .................................................................
        if (rootShadow.m_type == 1) {
            shadowTextures[rootShadow.m_index] = rootShadow.m_depthMap;
            b2Vec2 rootBodyPos = rootBody.m_body->GetPosition();
            glm::vec3 rootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.0f);
            glm::vec3 offsetRootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.1f);

            glm::mat4 rootProjection = glm::perspective(glm::radians(35.0f), (GLfloat)m_shadowWidth / (GLfloat)m_shadowHeight, rootShadow.m_nearPlane, rootShadow.m_farPlane);
            glm::mat4 rootView = glm::lookAt(offsetRootPos, rootPos + rootLight.m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rootSpaceMatrix = rootProjection * rootView;

            glUseProgram(rootShader.m_lightProgram);
            std::string lightSpaceMatrixAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].lightSpaceMatrix";
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_lightProgram, lightSpaceMatrixAddress.c_str()), 1, GL_FALSE, &rootSpaceMatrix[0][0]);
            glUseProgram(rootShader.m_shadowProgram);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, "lightSpaceMatrix"), 1, GL_FALSE, &rootSpaceMatrix[0][0]);

            glViewport(0, 0, m_shadowWidth, m_shadowHeight);
            glBindFramebuffer(GL_FRAMEBUFFER, rootShadow.m_shadowFramebuffer);
            glClear(GL_DEPTH_BUFFER_BIT);
            // render objects that cast a shadow to the 2D shadow map texture
            gameplayEntities.each([&](
                const auto& gameMaterial,
                const auto& gameBody,
                const auto& gameTexture,
                const auto& gameShader,
                const auto& gameGraphics
            ) {
                b2Vec2 gameBodyPos = gameBody.m_body->GetPosition();
                glm::vec3 gamePos = glm::vec3(gameBodyPos.x, gameBodyPos.y, 0.0f);
                if (glm::distance(rootPos, gamePos) <= rootShadow.m_farPlane) {
                    float gameAngle = gameBody.m_body->GetAngle();
                    glm::mat4 gameModel = glm::mat4(1.0f);
                    gameModel = glm::translate(gameModel, gamePos);
                    gameModel = glm::rotate(gameModel, gameAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                    glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, "model"), 1, GL_FALSE, &gameModel[0][0]);
                    glBindVertexArray(gameGraphics.m_VAO);
                    glDrawArrays(GL_TRIANGLES, 0, gameGraphics.m_vertexCount);
                    glBindVertexArray(0);
                }
            });
            lightEntities.each([&](
                const auto& interiorLight,
                const auto& interiorBody,
                const auto& interiorShader,
                const auto& interiorGraphics,
                const auto& interiorShadow
            ) {
                // if point or spot light, it will cast a shadow
                if (interiorLight.m_type != 0) {
                    b2Vec2 interiorBodyPos = interiorBody.m_body->GetPosition();
                    glm::vec3 interiorPos = glm::vec3(interiorBodyPos.x, interiorBodyPos.y, 0.0f);
                    if (glm::distance(rootPos, interiorPos) <= rootShadow.m_farPlane) {
                        float interiorAngle = interiorBody.m_body->GetAngle();
                        glm::mat4 interiorModel = glm::mat4(1.0f);
                        interiorModel = glm::translate(interiorModel, interiorPos);
                        interiorModel = glm::rotate(interiorModel, interiorAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                        interiorModel = glm::scale(interiorModel, interiorLight.m_scale);
                        glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, "model"), 1, GL_FALSE, &interiorModel[0][0]);
                        glBindVertexArray(interiorGraphics.m_VAO);
                        glDrawArrays(GL_TRIANGLES, 0, interiorGraphics.m_vertexCount);
                        glBindVertexArray(0);
                    }
                }
            });
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, framebufferWidth, framebufferHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        // .................................................................
        // pointlight: omnidirectional shadow mapping
        // .................................................................
        else if (rootShadow.m_type == 2) {
            shadowCubes[rootShadow.m_index] = rootShadow.m_depthCubemap;
            b2Vec2 rootBodyPos = rootBody.m_body->GetPosition();
            glm::vec3 rootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.0f);
            glm::vec3 offsetRootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.1f);

            glUseProgram(rootShader.m_lightProgram);
            std::string farPlaneAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].farPlane";
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, farPlaneAddress.c_str()), rootShadow.m_farPlane);

            glm::mat4 rootProjection = glm::perspective(glm::radians(90.0f), (GLfloat)m_shadowWidth / (GLfloat)m_shadowHeight, rootShadow.m_nearPlane, rootShadow.m_farPlane);
            std::vector<glm::mat4> rootTransforms;
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
            rootTransforms.push_back(rootProjection * glm::lookAt(offsetRootPos, rootPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

            glUseProgram(rootShader.m_shadowProgram);
            std::string uniformName;
            for (unsigned int i = 0; i < 6; ++i) {
                uniformName = "shadowMatrices[" + std::to_string(i) + "]";
                glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, uniformName.c_str()), 1, GL_FALSE, &(rootTransforms[i])[0][0]);
            }
            glUniform1f(glGetUniformLocation(rootShader.m_shadowProgram, "far_plane"), rootShadow.m_farPlane);
            glUniform3fv(glGetUniformLocation(rootShader.m_shadowProgram, "lightPos"), 1, &offsetRootPos[0]); 

            glViewport(0, 0, m_shadowWidth, m_shadowHeight);
            glBindFramebuffer(GL_FRAMEBUFFER, rootShadow.m_shadowFramebuffer);
            glClear(GL_DEPTH_BUFFER_BIT);
            // render objects that cast a shadow to the 3D shadow map cubemap
            gameplayEntities.each([&](
                const auto& gameMaterial,
                const auto& gameBody,
                const auto& gameTexture,
                const auto& gameShader,
                const auto& gameGraphics
            ) {
                b2Vec2 gameBodyPos = gameBody.m_body->GetPosition();
                glm::vec3 gamePos = glm::vec3(gameBodyPos.x, gameBodyPos.y, 0.0f);
                if (glm::distance(rootPos, gamePos) <= rootShadow.m_farPlane) {
                    float gameAngle = gameBody.m_body->GetAngle();
                    glm::mat4 gameModel = glm::mat4(1.0f);
                    gameModel = glm::translate(gameModel, gamePos);
                    gameModel = glm::rotate(gameModel, gameAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                    glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, "model"), 1, GL_FALSE, &gameModel[0][0]);
                    glBindVertexArray(gameGraphics.m_VAO);
                    glDrawArrays(GL_TRIANGLES, 0, gameGraphics.m_vertexCount);
                    glBindVertexArray(0);
                }
            });
            lightEntities.each([&](
                const auto& interiorLight,
                const auto& interiorBody,
                const auto& interiorShader,
                const auto& interiorGraphics,
                const auto& interiorShadow
            ) {
                // if point or spot light, it will cast a shadow
                if (interiorLight.m_type != 0) {
                    b2Vec2 interiorBodyPos = interiorBody.m_body->GetPosition();
                    glm::vec3 interiorPos = glm::vec3(interiorBodyPos.x, interiorBodyPos.y, 0.0f);
                    if (glm::distance(rootPos, interiorPos) <= rootShadow.m_farPlane) {
                        float interiorAngle = interiorBody.m_body->GetAngle();
                        glm::mat4 interiorModel = glm::mat4(1.0f);
                        interiorModel = glm::translate(interiorModel, interiorPos);
                        interiorModel = glm::rotate(interiorModel, interiorAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                        interiorModel = glm::scale(interiorModel, interiorLight.m_scale);
                        glUniformMatrix4fv(glGetUniformLocation(rootShader.m_shadowProgram, "model"), 1, GL_FALSE, &interiorModel[0][0]);
                        glBindVertexArray(interiorGraphics.m_VAO);
                        glDrawArrays(GL_TRIANGLES, 0, interiorGraphics.m_vertexCount);
                        glBindVertexArray(0);
                    }
                }
            });
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, framebufferWidth, framebufferHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 3) store reflection data and render lights
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    lightEntities.each([&](
        const auto& rootLight,
        const auto& rootBody,
        const auto& rootShader,
        const auto& rootGraphics,
        const auto& rootShadow
    ) {
        // .....................................................................
        // directional lights
        // .....................................................................
        if (rootLight.m_type == 0) {
            glUseProgram(rootShader.m_lightProgram);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, "dirLight.direction"), rootLight.m_direction[0], rootLight.m_direction[1], rootLight.m_direction[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, "dirLight.ambient"), rootLight.m_ambient[0], rootLight.m_ambient[1], rootLight.m_ambient[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, "dirLight.diffuse"), rootLight.m_diffuse[0], rootLight.m_diffuse[1], rootLight.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, "dirLight.specular"), rootLight.m_specular[0], rootLight.m_specular[1], rootLight.m_specular[2]);
        }
        // .....................................................................
        // point lights
        // .....................................................................
        else if (rootLight.m_type == 1) {
            b2Vec2 rootBodyPos = rootBody.m_body->GetPosition();
            glm::vec3 rootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.0f);
            glm::vec3 offsetRootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.1f);
            float rootAngle = rootBody.m_body->GetAngle();

            // .................................................................
            // pointlight: store reflection data
            std::string positionAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].position";
            std::string ambientAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].ambient";
            std::string diffuseAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].diffuse";
            std::string specularAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].specular";
            std::string constantAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].constant";
            std::string linearAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].linear";
            std::string quadraticAddress = "pointLights[" + std::to_string(rootShadow.m_index) + "].quadratic";
            glUseProgram(rootShader.m_lightProgram);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, positionAddress.c_str()), rootPos[0], rootPos[1], rootPos[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, ambientAddress.c_str()), rootLight.m_ambient[0], rootLight.m_ambient[1], rootLight.m_ambient[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, diffuseAddress.c_str()), rootLight.m_diffuse[0], rootLight.m_diffuse[1], rootLight.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, specularAddress.c_str()), rootLight.m_specular[0], rootLight.m_specular[1], rootLight.m_specular[2]);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, constantAddress.c_str()), rootLight.m_constant);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, linearAddress.c_str()), rootLight.m_linear);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, quadraticAddress.c_str()), rootLight.m_quadratic);

            // .................................................................
            // pointlight: render
            glm::mat4 pointProjection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
            glm::mat4 pointView = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
            glm::mat4 pointModel = glm::mat4(1.0f);
            glUseProgram(rootShader.m_outputProgram);
            glStencilMask(0x00);
            glUniform4f(glGetUniformLocation(rootShader.m_outputProgram, "LightColor"), rootLight.m_diffuse[0], rootLight.m_diffuse[1], rootLight.m_diffuse[2], 1.0f);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "projection"), 1, GL_FALSE, &pointProjection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "view"), 1, GL_FALSE, &pointView[0][0]);
            pointModel = glm::translate(pointModel, rootPos);
            pointModel = glm::rotate(pointModel, rootAngle, glm::vec3(0.0f, 0.0f, 1.0f));
            pointModel = glm::scale(pointModel, rootLight.m_scale);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "model"), 1, GL_FALSE, &pointModel[0][0]);
            glBindVertexArray(rootGraphics.m_VAO);
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, rootGraphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
            glBindVertexArray(0);
        }
        // .....................................................................
        // spot lights
        // .....................................................................
        else {
            b2Vec2 rootBodyPos = rootBody.m_body->GetPosition();
            glm::vec3 rootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.0f);
            glm::vec3 offsetRootPos = glm::vec3(rootBodyPos.x, rootBodyPos.y, 0.1f);
            float rootAngle = rootBody.m_body->GetAngle();

            // .................................................................
            // spotlight: store reflection data
            std::string positionAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].position";
            std::string directionAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].direction";
            std::string ambientAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].ambient";
            std::string diffuseAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].diffuse";
            std::string specularAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].specular";
            std::string constantAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].constant";
            std::string linearAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].linear";
            std::string quadraticAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].quadratic";
            std::string cutOffAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].cutOff";
            std::string outerCutOffAddress = "spotLights[" + std::to_string(rootShadow.m_index) + "].outerCutOff";
            glUseProgram(rootShader.m_lightProgram);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, positionAddress.c_str()), rootPos[0], rootPos[1], rootPos[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, directionAddress.c_str()), rootLight.m_direction[0], rootLight.m_direction[1], rootLight.m_direction[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, ambientAddress.c_str()), rootLight.m_ambient[0], rootLight.m_ambient[1], rootLight.m_ambient[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, diffuseAddress.c_str()), rootLight.m_diffuse[0], rootLight.m_diffuse[1], rootLight.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(rootShader.m_lightProgram, specularAddress.c_str()), rootLight.m_specular[0], rootLight.m_specular[1], rootLight.m_specular[2]);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, constantAddress.c_str()), rootLight.m_constant);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, linearAddress.c_str()), rootLight.m_linear);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, quadraticAddress.c_str()), rootLight.m_quadratic);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, cutOffAddress.c_str()), rootLight.m_cutOff);
            glUniform1f(glGetUniformLocation(rootShader.m_lightProgram, outerCutOffAddress.c_str()), rootLight.m_outerCutOff);

            // .................................................................
            // spotlight: render
            glm::mat4 spotProjection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
            glm::mat4 spotView = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
            glm::mat4 spotModel = glm::mat4(1.0f);
            glUseProgram(rootShader.m_outputProgram);
            glStencilMask(0x00);
            glUniform4f(glGetUniformLocation(rootShader.m_outputProgram, "LightColor"), rootLight.m_diffuse[0], rootLight.m_diffuse[1], rootLight.m_diffuse[2], 1.0f);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "projection"), 1, GL_FALSE, &spotProjection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "view"), 1, GL_FALSE, &spotView[0][0]);
            spotModel = glm::translate(spotModel, rootPos);
            spotModel = glm::rotate(spotModel, rootAngle, glm::vec3(0.0f, 0.0f, 1.0f));
            spotModel = glm::scale(spotModel, rootLight.m_scale);
            glUniformMatrix4fv(glGetUniformLocation(rootShader.m_outputProgram, "model"), 1, GL_FALSE, &spotModel[0][0]);
            glBindVertexArray(rootGraphics.m_VAO);
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, rootGraphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
            glBindVertexArray(0);
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 4) render skybox
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto skyboxEntities = registry.view<
        SkyboxComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    skyboxEntities.each([&](
        const auto& skybox,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
        glUseProgram(shader.m_outputProgram);

        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        // remove translation from view matrix
        glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp)));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "view"), 1, GL_FALSE, &view[0][0]);

        glBindVertexArray(graphics.m_VAO);
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture.m_cubemap);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        glDisable(GL_FRAMEBUFFER_SRGB);
        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 5) render game entities with material components
    // _________________________________________________________________________
    // -------------------------------------------------------------------------

    gameplayEntities.each([&](
        const auto& material,
        const auto& body,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        b2Vec2 bodyPos = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();
        
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normal = glm::mat3(1.0f);
        
        glUseProgram(shader.m_outputProgram);
        if (graphics.m_stencilFlag == true) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
        }
        else {
            glStencilMask(0x00);
        }
        glUniform1f(glGetUniformLocation(shader.m_outputProgram, "material.shininess"), material.m_shininess);
        glUniform3f(glGetUniformLocation(shader.m_outputProgram, "viewPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "view"), 1, GL_FALSE, &view[0][0]);
        model = glm::translate(model, glm::vec3(bodyPos.x, bodyPos.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "model"), 1, GL_FALSE, &model[0][0]);
        normal = glm::mat3(transpose(inverse(model)));
        glUniformMatrix3fv(glGetUniformLocation(shader.m_outputProgram, "normal"), 1, GL_FALSE, &normal[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture.m_specular);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture.m_normal);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, shadowTextures[0]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, shadowTextures[1]);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, shadowTextures[2]);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubes[0]);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubes[1]);
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubes[2]);
        glBindVertexArray(graphics.m_VAO);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        glDisable(GL_FRAMEBUFFER_SRGB);
        glBindVertexArray(0);
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 6) render sprites
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto spriteEntities = registry.view<
        SpriteComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    spriteEntities.each([&](
        const auto& sprite,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) { 
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        glUseProgram(shader.m_outputProgram);
        glStencilMask(0x00);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "view"), 1, GL_FALSE, &view[0][0]);
        model = glm::translate(model, sprite.m_position);
        model = glm::rotate(model, sprite.m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, sprite.m_scale);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_outputProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        glBindVertexArray(graphics.m_VAO);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        glDisable(GL_FRAMEBUFFER_SRGB);
        glBindVertexArray(0);
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 7) render text
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto textEntities = registry.view<
        TextComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    textEntities.each([&](
        auto& text,
        const auto& shader,
        const auto& graphics
    ) { 
        glUseProgram(shader.m_outputProgram);
        glStencilMask(0x00);
        glUniform3f(glGetUniformLocation(shader.m_outputProgram, "textColor"), text.m_color.x, text.m_color.y, text.m_color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(graphics.m_VAO);

        float x = text.m_xCoord;
        // iterate through all characters
        for (std::vector<Character>::iterator ch = text.m_characters.begin(); ch != text.m_characters.end(); ++ch) {
            float xpos = x + ch->m_bearing.x * text.m_scale;
            float ypos = text.m_yCoord - (ch->m_size.y - ch->m_bearing.y) * text.m_scale;
            float w = ch->m_size.x * text.m_scale;
            float h = ch->m_size.y * text.m_scale;
            // update VBO for each character
            float textVertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->m_textureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, graphics.m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textVertices), textVertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels 
            // by 64 to get amount of pixels))
            x += (ch->m_advance >> 6) * text.m_scale;
        }
        x = text.m_xCoord;

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 8) render stencil outlines
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    gameplayEntities.each([&](
        const auto& material,
        const auto& body,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        if (graphics.m_stencilFlag == true) {
            b2Vec2 bodyPos = body.m_body->GetPosition();
            float angle = body.m_body->GetAngle();

            glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat3 normal = glm::mat3(1.0f);
            float scale = 1.1f;

            glUseProgram(shader.m_stencilProgram);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);

            glUniformMatrix4fv(glGetUniformLocation(shader.m_stencilProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_stencilProgram, "view"), 1, GL_FALSE, &view[0][0]);
            model = glm::translate(model, glm::vec3(bodyPos.x, bodyPos.y, 0.0f));
            model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            glUniformMatrix4fv(glGetUniformLocation(shader.m_stencilProgram, "model"), 1, GL_FALSE, &model[0][0]);
            normal = glm::mat3(transpose(inverse(model)));
            glUniformMatrix3fv(glGetUniformLocation(shader.m_stencilProgram, "normal"), 1, GL_FALSE, &normal[0][0]);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture.m_specular);
            glBindVertexArray(graphics.m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);

            glBindVertexArray(0);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable(GL_DEPTH_TEST);
        }
    });
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Extra Functionality
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void RenderSystem::setWindowPointer(GLFWwindow* glfwWindow) {
    m_glfwWindow = glfwWindow;
    glfwGetWindowSize(m_glfwWindow, &m_screenWidth, &m_screenHeight);

    // keyboard input
    auto framebuffer_callback = [](GLFWwindow* window, int width, int height) {
        static_cast<RenderSystem*>(glfwGetWindowUserPointer(window))->handleFramebufferResize(window, width, height);
    };
    glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_callback);
}

void RenderSystem::handleFramebufferResize(GLFWwindow* window, int width, int height) {
    // gets called when window first displayed and any subsequent resizing 
    // glViewport maps OpenGL's coordinates into screen coordinates
    //  - OpenGL coordinates (both x and y) will range from (-1 to 1) 
    //  - we must map those coordinates to (0, width) and (0, height)
    glViewport(
        0,          // lower left corner x-coordinate
        0,          // lower left corner y-coordinate
        width,      // width of viewport 
        height      // height of viewport
    );
}

void RenderSystem::setGammaFlag(bool gammaFlag) {
    m_gammaFlag = gammaFlag;
}

void RenderSystem::setShadowResolution(unsigned int shadowWidth, unsigned int shadowHeight) {
    m_shadowWidth = shadowWidth;
    m_shadowHeight = shadowHeight;
}

void RenderSystem::deleteBuffers(entt::registry& registry) {
    auto buffers = registry.view<RenderDataComponent>();
    buffers.each([&](auto& graphics) {
        glDeleteVertexArrays(1, &graphics.m_VAO);
        glDeleteBuffers(1, &graphics.m_VBO);
    });
    auto framebuffers = registry.view<ShadowFramebufferComponent>();
    framebuffers.each([&](auto& shadow) {
        glDeleteFramebuffers(1, &shadow.m_shadowFramebuffer);
        glDeleteTextures(1, &shadow.m_depthMap);
        glDeleteTextures(1, &shadow.m_depthCubemap);
    });
}