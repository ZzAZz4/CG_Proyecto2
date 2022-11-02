#version 450 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout (location = 0) in vec4 position;
layout (location = 1) in uint normal;

out vec4 texcoord;
out vec4 modelCoords;
out vec3 fragnormal;
flat out uint fragNormalFlags;
flat out uint face;

uint bit(uint x, uint n) {
    return (x >> n) & 1u;
}

void main() {
    texcoord = position;
    modelCoords = model * vec4(position.xyz, 1.0);

    fragnormal = -(-1 * float(normal & 1u)) * vec3(normal & 2u, normal & 4u, normal & 8u);
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
    fragNormalFlags = normal;
    face = bit(normal, 0) + 2 * bit(normal, 2) + 4 * bit(normal, 3);
}
