// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.cpp
//  implementation of Render System 
// -----------------------------------------------------------------------------

#include "system_render.h"

/*
    1) store camera data
    2) render shadow depth maps to shadow framebuffer
    3) store light data and render point lights & spot lights
    4) render skybox
    5) render game objects (with material comp)
    6) render sprites
    7) render stencil outlines
*/

void RenderSystem::update(
    const float timeStep, 
    entt::registry& registry
) {
    // objects will be needed for rendering to shadowmaps prior to screen
    auto objects = registry.view<
        MaterialComponent,
        BodyTransformComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 1) iterate over camera entities to store camera data
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // camera and light data
    float cameraZoom;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    // int pointSourceCount;

    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](const auto& camera) {
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
    // 2) render shadow depth maps to shadow framebuffer
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // variables needed for rendering depth map to shadow framebuffer
    int fbWidth;
    int fbHeight;
    glfwGetFramebufferSize(m_glfwWindow, &fbWidth, &fbHeight);
    // variables needed for later rendering to screen using depthmap as texture
    glm::vec3 testPos = glm::vec3(0.0f, 10.0f, 0.0f);
    glm::mat4 lightSpaceMatrix;
    unsigned int depthMap;

    auto lights = registry.view<
        LightComponent,
        BodyTransformComponent,
        ShaderProgramComponent,
        LightShaderProgramComponent,
        RenderDataComponent,
        ShadowFramebufferComponent
    >();
    lights.each([&](
        const auto& depthLight,
        const auto& depthBody,
        const auto& depthShader,
        const auto& depthLightShader,
        const auto& depthGraphics,
        const auto& depthShadow
    ) {
        if (depthLight.m_type == 0) {
            glm::mat4 lightProjection; 
            glm::mat4 lightView;
            float near_plane = 1.0f;
            float far_plane = 20.0f;
            // lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            // lightView = glm::lookAt(cameraPosition + testPos, cameraPosition + cameraFront, glm::vec3(0.0, 1.0, 0.0));
            lightView = glm::lookAt(testPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
            lightSpaceMatrix = lightProjection * lightView;
            depthMap = depthShadow.m_depthMap;

            // render scene from light's point of view
            glUseProgram(depthLightShader.m_depthMapProgram);
            glUniformMatrix4fv(glGetUniformLocation(depthLightShader.m_depthMapProgram, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);
            glViewport(0, 0, m_shadowWidth, m_shadowHeight);
            glBindFramebuffer(GL_FRAMEBUFFER, depthShadow.m_shadowFramebuffer);
            glClear(GL_DEPTH_BUFFER_BIT);

            // render point and spot lights to depth map
            lights.each([&](
                const auto& ltLight,
                const auto& ltBody,
                const auto& ltShader,
                const auto& ltLightShader,
                const auto& ltGraphics,
                const auto& ltShadow
            ) {
                if (ltLight.m_type != 0) {

                b2Vec2 ltBodyPos = ltBody.m_body->GetPosition();
                float ltAngle = ltBody.m_body->GetAngle();

                glm::mat4 ltModel = glm::mat4(1.0f);
                ltModel = glm::translate(ltModel, glm::vec3(ltBodyPos.x, ltBodyPos.y, 0.0f));
                ltModel = glm::rotate(ltModel, ltAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                ltModel = glm::scale(ltModel, ltLight.m_scale);
                glUniformMatrix4fv(glGetUniformLocation(depthLightShader.m_depthMapProgram, "model"), 1, GL_FALSE, &ltModel[0][0]);

                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, 12);
                glBindVertexArray(ltGraphics.m_VAO);
                glDrawArrays(GL_TRIANGLES, 0, ltGraphics.m_vertexCount);
                }
            });
            // render objects to depth map
            objects.each([&](
                const auto& objMaterial,
                const auto& objBody,
                const auto& objTexture,
                const auto& objShader,
                const auto& objGraphics
            ) {
                b2Vec2 objBodyPos = objBody.m_body->GetPosition();
                float objAngle = objBody.m_body->GetAngle();

                glm::mat4 objModel = glm::mat4(1.0f);
                objModel = glm::translate(objModel, glm::vec3(objBodyPos.x, objBodyPos.y, 0.0f));
                objModel = glm::rotate(objModel, objAngle, glm::vec3(0.0f, 0.0f, 1.0f));
                glUniformMatrix4fv(glGetUniformLocation(depthLightShader.m_depthMapProgram, "model"), 1, GL_FALSE, &objModel[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, objTexture.m_diffuse);
                glBindVertexArray(objGraphics.m_VAO);
                glDrawArrays(GL_TRIANGLES, 0, objGraphics.m_vertexCount);
            });

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // reset viewport
            glViewport(0, 0, fbWidth, fbHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    });

    // render the depth map texture for testing
    auto quads = registry.view<
        QuadComponent,
        ShaderProgramComponent,
        RenderDataComponent
    >();
    quads.each([&](
        const auto& quad,
        const auto& quadShader,
        const auto& quadGraphics
    ) {
        glUseProgram(quadShader.m_shaderProgram);
        glBindVertexArray(quadGraphics.m_VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    });

/*
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 3) iterate over light entities for light data and screen rendering
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    lights.each([&](
        const auto& light,
        const auto& body,
        const auto& shader,
        const auto& lightShader,
        const auto& graphics,
        const auto& shadow
    ) {
        // prepare matrices for rendering point and spot lights
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        // _____________________________________________________________________
        // if directional light
        // ---------------------------------------------------------------------
        if (light.m_type == 0) {
            // save directional light data for rendering game objects in step 3) of update()
            glUseProgram(lightShader.m_reflectorProgram);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "dirLight.direction"), light.m_direction[0], light.m_direction[1], light.m_direction[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "dirLight.ambient"), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "dirLight.diffuse"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "dirLight.specular"), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
        }
        // _____________________________________________________________________
        // if point light
        // ---------------------------------------------------------------------
        else if (light.m_type == 1) {
            b2Vec2 bodyPos = body.m_body->GetPosition();
            glm::vec3 lightPos(bodyPos.x, bodyPos.y, 0.0f);
            float angle = body.m_body->GetAngle();

            // save point light data for rendering game objects in step 3) of update()
            std::string positionAddress = "pointLights[" + std::to_string(pointSourceCount) + "].position";
            std::string ambientAddress = "pointLights[" + std::to_string(pointSourceCount) + "].ambient";
            std::string diffuseAddress = "pointLights[" + std::to_string(pointSourceCount) + "].diffuse";
            std::string specularAddress = "pointLights[" + std::to_string(pointSourceCount) + "].specular";
            std::string constantAddress = "pointLights[" + std::to_string(pointSourceCount) + "].constant";
            std::string linearAddress = "pointLights[" + std::to_string(pointSourceCount) + "].linear";
            std::string quadraticAddress = "pointLights[" + std::to_string(pointSourceCount) + "].quadratic";
            glUseProgram(lightShader.m_reflectorProgram);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, positionAddress.c_str()), lightPos[0], lightPos[1], lightPos[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, ambientAddress.c_str()), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, diffuseAddress.c_str()), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, specularAddress.c_str()), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, constantAddress.c_str()), light.m_constant);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, linearAddress.c_str()), light.m_linear);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, quadraticAddress.c_str()), light.m_quadratic);
            pointSourceCount++;

            // now render the point light source to window
            glUseProgram(shader.m_shaderProgram);
            glStencilMask(0x00);
            glUniform4f(glGetUniformLocation(shader.m_shaderProgram, "LightColor"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2], 1.0f);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
            model = glm::translate(model, lightPos);
            model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, light.m_scale);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
            glBindVertexArray(graphics.m_VAO);
            if (m_gammaFlag) {
                glEnable(GL_FRAMEBUFFER_SRGB);
                glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
                glDisable(GL_FRAMEBUFFER_SRGB);
            }
            else {
                glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            }
        }
        // _____________________________________________________________________
        // if spot light
        // ---------------------------------------------------------------------
        else {
            b2Vec2 bodyPos = body.m_body->GetPosition();
            glm::vec3 lightPos(bodyPos.x, bodyPos.y, 0.0f);
            float angle = body.m_body->GetAngle();

            // save spotlight data for rendering game objects in step 3) of update()
            glUseProgram(lightShader.m_reflectorProgram);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.position"), lightPos[0], lightPos[1], lightPos[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.direction"), light.m_direction[0], light.m_direction[1], light.m_direction[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.ambient"), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.diffuse"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.specular"), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.constant"), light.m_constant);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.linear"), light.m_linear);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.quadratic"), light.m_quadratic);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.cutOff"), light.m_cutOff);
            glUniform1f(glGetUniformLocation(lightShader.m_reflectorProgram, "spotLight.outerCutOff"), light.m_outerCutOff);

            // now render the spotlight source to window
            glUseProgram(shader.m_shaderProgram);
            glStencilMask(0x00);
            glUniform4f(glGetUniformLocation(shader.m_shaderProgram, "LightColor"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2], 1.0f);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
            model = glm::translate(model, lightPos);
            model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, light.m_scale);
            glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
            glBindVertexArray(graphics.m_VAO);
            if (m_gammaFlag) {
                glEnable(GL_FRAMEBUFFER_SRGB);
                glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
                glDisable(GL_FRAMEBUFFER_SRGB);
            }
            else {
                glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            }
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 4) render skybox
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto skyboxes = registry.view<
        SkyboxComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    skyboxes.each([&](
        const auto& skybox,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
        glUseProgram(shader.m_shaderProgram);

        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        // remove translation from view matrix
        glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp)));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        glBindVertexArray(graphics.m_VAO);
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture.m_cubemap);
        if (m_gammaFlag) {
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 5) iterate over game objects/entities to render to screen
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    objects.each([&](
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
        
        glUseProgram(shader.m_shaderProgram);
        if (graphics.m_stencilFlag == true) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
        }
        else {
            glStencilMask(0x00);
        }
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "viewPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        model = glm::translate(model, glm::vec3(bodyPos.x, bodyPos.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "lightPos"), testPos[0], testPos[1], testPos[2]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glBindVertexArray(graphics.m_VAO);
        if (m_gammaFlag) {
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
    });


    objects.each([&](
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
        
        glUseProgram(shader.m_shaderProgram);
        if (graphics.m_stencilFlag == true) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
        }
        else {
            glStencilMask(0x00);
        }
        glUniform1i(glGetUniformLocation(shader.m_shaderProgram, "blinn"), true); 
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "viewPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);
        glUniform1f(glGetUniformLocation(shader.m_shaderProgram, "material.shininess"), material.m_shininess);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        model = glm::translate(model, glm::vec3(bodyPos.x, bodyPos.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        normal = glm::mat3(transpose(inverse(model)));
        glUniformMatrix3fv(glGetUniformLocation(shader.m_shaderProgram, "normal"), 1, GL_FALSE, &normal[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture.m_specular);
        glBindVertexArray(graphics.m_VAO);
        if (m_gammaFlag) {
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
    });


    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 6) iterate over sprite entities to render
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto sprites = registry.view<
        SpriteComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    sprites.each([&](
        const auto& sprite,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) { 
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        glUseProgram(shader.m_shaderProgram);
        glStencilMask(0x00);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        model = glm::translate(model, sprite.m_position);
        model = glm::rotate(model, sprite.m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, sprite.m_scale);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        glBindVertexArray(graphics.m_VAO);
        if (m_gammaFlag) {
            glEnable(GL_FRAMEBUFFER_SRGB);
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
            glDisable(GL_FRAMEBUFFER_SRGB);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 7) iterate over game object entities to stencil outline
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    objects.each([&](
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
*/
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
    });
}