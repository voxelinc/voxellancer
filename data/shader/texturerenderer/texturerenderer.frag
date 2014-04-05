#version 330

uniform sampler2D tex;

in vec2 v_tex;

layout(location=0) out vec4 fragColor;
layout(location=1) out vec4 normalz;

void main() {
    fragColor = texture(tex, v_tex.xy);
}
