#version 330

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 normalz;
layout (location = 2) out vec4 emissiveness;

void main() {
    vec4 color = vec4(0.3, 1.0, 0.3, 1.0);

    fragColor = color;
    normalz = vec4(0.0, 0.0, 1.0, gl_FragCoord.z);
    emissiveness = color;
}

