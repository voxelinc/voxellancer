#version 330

uniform ivec2 viewport;
uniform sampler2D source;

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

in vec2 v_uv;

layout(location=0) out vec4 fragColor;

void main() {
    vec4 sum = texture(source, v_uv) * weight[0];
    for(int i=1; i<3; i++) {
        sum += texture(source, vec2(v_uv.x + offset[i]/viewport.x, v_uv.y)) * weight[i];
        sum += texture(source, vec2(v_uv.x - offset[i]/viewport.x, v_uv.y)) * weight[i];
    }
    fragColor = sum;
}
