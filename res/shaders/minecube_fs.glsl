#version 450 core

in vec4 texcoord;
out vec4 fragColor;

uniform sampler2DArray tex;
uniform float illumination;

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

float closest(float x, float divisions) {
    return floor(x * divisions) / divisions;
}


vec4 calculate_color() {
    if (texcoord.w > 0.0) {
        return 0.85 * texture(tex,
            vec3(
                closest(fract(texcoord.x + texcoord.z), 16),
                closest(fract(texcoord.y), 16),
                texcoord.w - 1.0
            )
        );
    }
    else {
        return texture(tex,
            vec3(
                closest(fract(texcoord.x + texcoord.y), 16),
                closest(fract(texcoord.z), 16),
                -texcoord.w - 1.0
            )
        );
    };
}

void main() {
    vec4 color = illumination * calculate_color();

    if (color.a < 0.1) {
        discard;
    }

    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fog = clamp(exp(-fogdensity * z * z), 0.2, 1);


    fragColor = mix(fogcolor, color, fog);
}
