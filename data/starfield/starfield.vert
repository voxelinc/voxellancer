#version 150

uniform mat4 viewProjection;

in vec3 a_vertex;
in float a_brightness;
in float a_size;

out vec4 pos;
out float brightness;
out float size;

void main()
{
    brightness = a_brightness;
    size = a_size;
    pos = viewProjection * vec4(a_vertex, 1.0);
}
