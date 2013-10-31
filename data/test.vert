#version 330

uniform mat4 modelView;
uniform mat4 projection;
uniform mat4 projection_actual;

in vec3 a_vertex;
out vec3 v_tex;

void main()
{
	v_tex = (projection_actual * vec4(a_vertex.x, a_vertex.y, a_vertex.z, 1.0)).xyz;
	v_tex.x = -v_tex.x;

	gl_Position = projection * modelView * vec4(a_vertex, 1.0);
}
