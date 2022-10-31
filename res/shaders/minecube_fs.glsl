#version 330 core

in vec4 texcoord;
uniform sampler2D tex;

float nearest_016(float x) {
    return floor(x * 16.0) / 16.0;
}

void main() {
    if (texcoord.w > 0.0){
        gl_FragColor = texture(tex, vec2(
            (texcoord.w - 1 + (fract(texcoord.x + texcoord.z))) / 16.0,
            (fract(texcoord.y)) / 16.0)
        );
    } else {
        gl_FragColor = texture(tex, vec2(
            (-texcoord.w - 1 + (fract(texcoord.x + texcoord.y))) / 16.0,
            (fract(texcoord.z)) / 16.0)
        );
    }
}
