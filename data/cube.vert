#version 330

uniform mat4 modelView;
uniform mat4 projection;

in vec3 a_vertex;
in vec3 a_normal;

out vec2 v_uv;
out vec3 normal;
out vec4 position;

void main()
{
	v_uv = a_vertex.xy;
	gl_Position = projection * modelView * vec4(a_vertex, 1.0);
    normal = projection * modelView * vec4(a_normal, 0.0);
    position = projection * modelView * vec4(a_vertex, 1.0);

}
