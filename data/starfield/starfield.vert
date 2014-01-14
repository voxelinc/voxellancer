#version 150

uniform mat4 viewProjection;
uniform mat4 oldViewProjection;

in vec3 a_vertex;
in float a_brightness;
in float a_size;

out vec4 g_pos;
out vec4 g_oldPos;
out float g_brightness;
out float g_size;

void main()
{
    g_brightness = a_brightness;
    g_size = a_size;
    g_pos = viewProjection * vec4(a_vertex, 1.0);
    g_oldPos = oldViewProjection * vec4(a_vertex, 1.0);
}
