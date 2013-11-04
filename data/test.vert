#version 330

uniform mat4 viewInverted;
uniform mat4 projection; // no model - coordinates are in camera space

in vec3 a_vertex;
out vec3 v_tex;

void main()
{
	v_tex = (viewInverted * vec4(a_vertex, 1.0)).xyz;
	v_tex.x = -v_tex.x; // we want to see the cube from the inside

	gl_Position = projection * vec4(a_vertex, 1.0);
}
