#version 330

uniform vec4 speed;

in vec2 f_uv;
in float f_brightness;

layout(location=0) out vec4 fragColor;

const float MAX_ALPHA = 0.6;

void main() {
    // distance to center of star in  [0:1]
    float d = length(vec2(0.5) - f_uv)*2;

    fragColor = vec4(vec3(1.0), (MAX_ALPHA-d)*f_brightness);
    //fragColor = vec4(1.0);
}

