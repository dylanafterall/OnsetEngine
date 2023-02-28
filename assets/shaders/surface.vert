#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VERT_OUT {
    out vec3 FragPos;
    out vec3 Normal;
    out vec2 TexCoords;
} vert_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

void main() {
    vert_out.FragPos = vec3(model * vec4(aPos, 1.0f));
    vert_out.Normal = normal * aNormal;
    vert_out.TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(vert_out.FragPos, 1.0f);
}