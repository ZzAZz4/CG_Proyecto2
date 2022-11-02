#version 450 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec4 position;
layout (location = 1) in uint normal;

out vec4 texcoord;
out vec4 modelCoords;
out vec3 fragnormal;


void main() {
    texcoord = position;
    modelCoords = model * vec4(position.xyz, 1.0);

    fragnormal = -(-1 * float(normal & 1u)) * vec3(normal & 2u, normal & 4u, normal & 8u);
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
}
