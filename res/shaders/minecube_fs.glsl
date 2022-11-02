#version 450 core

const vec4 fogcolor = vec4(0.6, 0.8, 1.0, 1.0);
const float fogdensity = .00003;

uniform sampler2DArray tex[6];
uniform float ambientIllumination;
uniform vec3 lightSources[10];
uniform int lightSourcesCount;

in vec4 texcoord;
in vec4 modelCoords;
in vec3 fragnormal;
flat in uint fragNormalFlags;
flat in uint face;

out vec4 fragColor;

uint bit(uint x, uint n) {
    return (x >> n) & 1u;
}

bool lightInCube(vec3 a, vec3 b) {
    return abs(a.x - b.x) <= 0.5 && abs(a.y - b.y) <= 0.5 && abs(a.z - b.z) <= 0.5;
}

float calculateIllumination() {
    float illumination = ambientIllumination;
    for (int i = 0; i < lightSourcesCount; ++i) {
        if (lightInCube(modelCoords.xyz, lightSources[i])) {
            illumination += 1.0;

        }
        ivec3 lightSource = ivec3(lightSources[i]);
        vec3 lightDir = lightSources[i] - modelCoords.xyz;
        float distance = length(lightSources[i] - modelCoords.xyz);
        vec3 lightDirNorm = lightDir / distance;
        float angle = dot(lightDirNorm, fragnormal);
        illumination += max(0, 25 * angle / ((distance + 1) * (distance + 1)));
    }
    return max(0, min(1.0, illumination));
}


float closest(float x, float divisions) {
    return floor(x * divisions) / divisions;
}

vec4 calculateColor() {
    if (bit(fragNormalFlags, 2) != 1u) {
        return 0.85 * texture(tex[face],
            vec3(
                closest(fract(texcoord.x + texcoord.z), 16),
                closest(fract(texcoord.y), 16),
                texcoord.w
            )
        );
    }
    else {
        return texture(tex[face],
            vec3(
                closest(fract(texcoord.x + texcoord.y), 16),
                closest(fract(texcoord.z), 16),
                texcoord.w
            )
        );
    };
}


void main() {
    float illumination = calculateIllumination();
    vec4 color = calculateColor();
    color = vec4(color.xyz * illumination, color.w);

    if (color.a < 0.1) {
        discard;
    }

    float z = gl_FragCoord.z / gl_FragCoord.w;
    float fog = clamp(exp(-fogdensity * z * z), 0.2, 1);

    fragColor = mix(fogcolor, color, fog);
}
