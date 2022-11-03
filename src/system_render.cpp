// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// system_render.cpp
//  implementation of Render System 
// -----------------------------------------------------------------------------

#include "system_render.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// update(): -------------------------------------------------------------------
void RenderSystem::update(
    const float timeStep, 
    entt::registry& registry,
    const unsigned int SCR_WIDTH,
    const unsigned int SCR_HEIGHT
) {
    float cameraZoom;
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    auto cameras = registry.view<CameraComponent>();
    cameras.each([&](const auto& camera) {
        cameraZoom = camera.m_zoom;
        cameraPosition = camera.m_position;
        cameraFront = camera.m_front;
        cameraUp = camera.m_up;
    });

    // retrieve a view of entities with applicable components
    auto polygons = registry.view<
        MeshCubeComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    // iterate over each entity in the view
    polygons.each([&](
        const auto& mesh,
        const auto& texture,
        const auto& shader,
        const auto& vao
    ) {
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_texture);

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
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, mesh.m_vertexCount);
    });
}

// deleteBuffers(): ------------------------------------------------------------
void RenderSystem::deleteBuffers(entt::registry& registry) {
    // retrieve a view of entities with applicable components
    auto buffers = registry.view<RenderBuffersComponent>();
    // iterate over each entity in the view
    buffers.each([&](auto& buffer) {
        glDeleteVertexArrays(1, &buffer.m_VAO);
        glDeleteBuffers(1, &buffer.m_VBO);
    });
}