// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.cpp
//  implementation of Render System 
// -----------------------------------------------------------------------------

#include "system_render.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void RenderSystem::update(
    const float timeStep, 
    entt::registry& registry,
    const unsigned int SCR_WIDTH,
    const unsigned int SCR_HEIGHT
) {
    // camera and light data
    float cameraZoom;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    int pointSourceCount;

    // 1) iterate over camera entities to store camera data
    // 2) iterate over light entities (dir / point / spot) to store light data
    // 3) iterate over game object (with material comp) entities to render
    // 4) iterate over sprite entities to render
    // 5) iterate over game object entities to stencil outline
    // 6) render skybox

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 1) iterate over camera entities to store camera data
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
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
    // 2) iterate over light entities (dir / point / spot) to store light data
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto lights = registry.view<
        LightComponent,
        BodyTransformComponent,
        ShaderProgramComponent,
        ReflectorShaderProgramComponent,
        RenderDataComponent
    >();
    lights.each([&](
        const auto& light,
        const auto& body,
        const auto& shader,
        const auto& reflector,
        const auto& graphics
    ) {
        // prepare matrices for rendering point and spot lights
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 model = glm::mat4(1.0f);

        // _________________________________________________________________________
        // if directional light
        // -------------------------------------------------------------------------
        if (light.m_type == 0) {
            // save directional light data for rendering game objects in step 3) of update()
            glUseProgram(reflector.m_shaderProgram);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "dirLight.direction"), light.m_direction[0], light.m_direction[1], light.m_direction[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "dirLight.ambient"), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "dirLight.diffuse"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "dirLight.specular"), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
        }
        // _________________________________________________________________________
        // if point light
        // -------------------------------------------------------------------------
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
            glUseProgram(reflector.m_shaderProgram);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, positionAddress.c_str()), lightPos[0], lightPos[1], lightPos[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, ambientAddress.c_str()), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, diffuseAddress.c_str()), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, specularAddress.c_str()), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, constantAddress.c_str()), light.m_constant);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, linearAddress.c_str()), light.m_linear);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, quadraticAddress.c_str()), light.m_quadratic);
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
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
        // _________________________________________________________________________
        // if spot light
        // -------------------------------------------------------------------------
        else {
            b2Vec2 bodyPos = body.m_body->GetPosition();
            glm::vec3 lightPos(bodyPos.x, bodyPos.y, 0.0f);
            float angle = body.m_body->GetAngle();

            // save spotlight data for rendering game objects in step 3) of update()
            glUseProgram(reflector.m_shaderProgram);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.position"), lightPos[0], lightPos[1], lightPos[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.direction"), light.m_direction[0], light.m_direction[1], light.m_direction[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.ambient"), light.m_ambient[0], light.m_ambient[1], light.m_ambient[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.diffuse"), light.m_diffuse[0], light.m_diffuse[1], light.m_diffuse[2]);
            glUniform3f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.specular"), light.m_specular[0], light.m_specular[1], light.m_specular[2]);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.constant"), light.m_constant);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.linear"), light.m_linear);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.quadratic"), light.m_quadratic);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.cutOff"), light.m_cutOff);
            glUniform1f(glGetUniformLocation(reflector.m_shaderProgram, "spotLight.outerCutOff"), light.m_outerCutOff);

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
            glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        }
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 6) render skybox
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

        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // remove translation from view matrix
        glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp)));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        glBindVertexArray(graphics.m_VAO);
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture.m_cubemap);
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 3) iterate over game object (with material comp) entities to render
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto objects = registry.view<
        MaterialComponent,
        BodyTransformComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    objects.each([&](
        const auto& material,
        const auto& body,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        b2Vec2 bodyPos = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();
        
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 4) iterate over sprite entities to render
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
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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
        glDrawArrays(GL_TRIANGLES, 0, graphics.m_vertexCount);
    });

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // 5) iterate over game object entities to stencil outline
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    auto stencils = registry.view<
        MaterialComponent,
        BodyTransformComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderDataComponent
    >();
    stencils.each([&](
        const auto& material,
        const auto& body,
        const auto& texture,
        const auto& shader,
        const auto& graphics
    ) {
        if (graphics.m_stencilFlag == true) {
            b2Vec2 bodyPos = body.m_body->GetPosition();
            float angle = body.m_body->GetAngle();

            glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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

void RenderSystem::deleteBuffers(entt::registry& registry) {
    auto buffers = registry.view<RenderDataComponent>();
    buffers.each([&](auto& graphics) {
        glDeleteVertexArrays(1, &graphics.m_VAO);
        glDeleteBuffers(1, &graphics.m_VBO);
    });
}