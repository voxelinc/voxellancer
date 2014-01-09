#version 130

uniform mat4 viewProjection;

in vec3 a_vertex;

out vec4 pos;

void main()
{
    pos = viewProjection * vec4(a_vertex, 1.0);
}
