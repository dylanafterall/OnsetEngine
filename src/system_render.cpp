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
void RenderSystem::update(const float timeStep, entt::registry& registry) {
    // retrieve a view of entities with applicable components
    auto polygons = registry.view<
        MeshOctagonComponent,
        TextureComponent, 
        ShaderProgramComponent,
        RenderBuffersComponent
    >();
    // iterate over each entity in the view
    polygons.each([&](
        auto& mesh,
        const auto& texture,
        const auto& shader,
        auto& vao
    ) {
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.m_texture);

        // prepare transformation matrix for translation, rotation, scale
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

        // get matrix's uniform location and set matrix
        glUseProgram(shader.m_shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shader.m_shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // render the entity
        glBindVertexArray(vao.m_VAO);
        glDrawElements(GL_TRIANGLES, mesh.m_indexCount, GL_UNSIGNED_INT, 0);
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
        glDeleteBuffers(1, &buffer.m_EBO);
    });
}