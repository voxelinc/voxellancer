#version 330

uniform mat4 viewProjection;
uniform mat4 oldViewProjection;

layout(location=0) in vec3 v_vertex;
layout(location=1) in float v_brightness;
layout(location=2) in float v_size;

out vec4 g_pos;
out vec4 g_oldPos;
out float g_brightness;
out float g_size;

void main() {
    g_brightness = v_brightness;
    g_size = v_size;
    g_pos = viewProjection * vec4(v_vertex, 1.0);
    g_oldPos = oldViewProjection * vec4(v_vertex, 1.0);
}

