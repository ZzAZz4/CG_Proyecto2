#version 450 core

layout (location = 0) in vec4 position;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 texcoord;
out vec4 modelCoords;
out float lightIllumination;



void main() {
    texcoord = position;
    modelCoords = model * vec4(position.xyz, 1.0);
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
}
