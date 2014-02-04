#version 330

uniform ivec2 viewport;

uniform sampler2D color;
uniform sampler2D bloom;

in vec2 v_uv;

layout(location=0) out vec4 fragColor;

void main() {
    fragColor = texture(color, v_uv) + texture(bloom, v_uv);
}