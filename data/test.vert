#version 330

uniform mat4 modelView;
uniform mat4 projection;

in vec3 a_vertex;
out vec2 v_uv;

void main()
{
	v_uv = vec2(a_vertex.x, 1.0f - a_vertex.y);
	gl_Position = projection * modelView * vec4(a_vertex, 1.0);
}
