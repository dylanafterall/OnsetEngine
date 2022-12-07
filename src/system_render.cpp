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
    // need access to camera data to render objects ----------------------------
    float cameraZoom;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    // need access to light data to render objects -----------------------------
    glm::vec3 lightPos;

    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](const auto& camera) {
        cameraZoom = camera.m_zoom;
        cameraPosition = camera.m_position;
        cameraFront = camera.m_front;
        cameraUp = camera.m_up;
    });

    // render light source test subject ------------------------------------
    auto lights = registry.view<
        LightComponent,
        BodyCircleComponent,
        MeshSphereComponent,
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    lights.each([&](
        const auto& light,
        const auto& body,
        const auto& mesh,
        const auto& shader,
        const auto& vao
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        lightPos = glm::vec3(position.x, position.y, 0.0f);
        float angle = body.m_body->GetAngle();

        // create transformations
        glUseProgram(shader.m_shaderProgram);
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // m_projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        // rendering the entity
        glBindVertexArray(vao.m_VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f)); // a smaller sphere
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });

    // now render ground floor -------------------------------------------------
    // retrieve a view of entities with applicable components
    auto ground = registry.view<
        BodyPolygonComponent,
        MeshGroundComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    // iterate over each entity in the view
    ground.each([&](
        const auto& body,
        const auto& mesh,
        const auto& texture,
        const auto& shader,
        const auto& vao
    ) {
        b2Vec2 position = body.m_body->GetPosition();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);

        // create transformations
        glUseProgram(shader.m_shaderProgram);
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // m_projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        // rendering the entity
        glBindVertexArray(vao.m_VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });

    // now render cubes --------------------------------------------------------
    // retrieve a view of entities with applicable components
    auto cubes = registry.view<
        BodyPolygonComponent,
        MeshCubeComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    // iterate over each entity in the view
    cubes.each([&](
        const auto& body,
        const auto& mesh,
        const auto& texture,
        const auto& shader,
        const auto& vao
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);

        // create transformations
        glUseProgram(shader.m_shaderProgram);
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // m_projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        // rendering the entity
        glBindVertexArray(vao.m_VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });

    // now render spheres ------------------------------------------------------
    auto spheres = registry.view<
        BodyCircleComponent,
        MeshSphereComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    spheres.each([&](
        const auto& body,
        const auto& mesh,
        const auto& texture,
        const auto& shader,
        const auto& vao
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);

        // create transformations
        glUseProgram(shader.m_shaderProgram);
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // m_projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // pass transformation matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        // rendering the entity
        glBindVertexArray(vao.m_VAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });

    // now render light reflection (color) test subject ------------------------
    auto colors = registry.view<
        ColorComponent,
        BodyCircleComponent,
        MeshSphereComponent,
        TextureComponent,
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    colors.each([&](
        const auto& color,
        const auto& body,
        const auto& mesh,
        const auto& texture,
        const auto& shader,
        const auto& vao
    ) {
        b2Vec2 position = body.m_body->GetPosition();
        float angle = body.m_body->GetAngle();

        glUseProgram(shader.m_shaderProgram);
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "light.position"), lightPos[0], lightPos[1], lightPos[2]);
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "viewPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);

        // light properties
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "light.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "light.diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(shader.m_shaderProgram, "light.specular"), 1.0f, 1.0f, 1.0f);

        // material properties
        glUniform1f(glGetUniformLocation(shader.m_shaderProgram, "material.shininess"), 64.0f);

        // create transformations
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // m_projection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        // pass transformation matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        // calculate normal matrix to pass to shader as uniform (better to use CPU than shader for inverse)
        glm::mat3 transposedInverse = glm::mat3(1.0f);
        transposedInverse = glm::mat3(transpose(inverse(model)));
        glUniformMatrix3fv(glGetUniformLocation(shader.m_shaderProgram, "transposedInverse"), 1, GL_FALSE, &transposedInverse[0][0]);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_diffuse);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture.m_specular);

        // rendering the entity
        glBindVertexArray(vao.m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });
}

void RenderSystem::deleteBuffers(entt::registry& registry) {
    // retrieve a view of entities with applicable components
    auto buffers = registry.view<RenderBuffersComponent>();
    // iterate over each entity in the view
    buffers.each([&](auto& buffer) {
        glDeleteVertexArrays(1, &buffer.m_VAO);
        glDeleteBuffers(1, &buffer.m_VBO);
    });
}