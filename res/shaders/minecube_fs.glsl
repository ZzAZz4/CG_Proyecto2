#version 330 core

in vec4 texcoord;
uniform sampler2DArray tex;

float closest(float x, float divisions) {
    return floor(x * divisions) / divisions;
}

void main() {
    if (texcoord.w > 0.0) {
        gl_FragColor = texture(tex,
            vec3(
                closest(fract(texcoord.x + texcoord.z), 16),
                closest(fract(texcoord.y), 16),
                texcoord.w - 1.0
            )
        );
    } else {
        gl_FragColor = texture(tex,
            vec3(
                closest(fract(texcoord.x + texcoord.y), 16),
                closest(fract(texcoord.z), 16),
                -texcoord.w - 1.0
            )
        );
    }
}
