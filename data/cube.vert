#version 410

uniform mat4 modelView;
uniform mat4 projection;

in vec3 a_vertex;
in vec3 a_normal;

out vec2 v_uv;
out vec3 normal;

void main()
{
	v_uv = a_vertex.xy;

    int x = gl_InstanceID / 100 - 5;
    int y = (gl_InstanceID / 10) % 10 - 5;
    int z = gl_InstanceID % 10 - 6;

    vec4 offset = vec4(x, y, z, 0.0f) / 3.0f;

	gl_Position = projection * (modelView * vec4(a_vertex, 1.0) + offset);
    
    normal = modelView * vec4(a_normal, 0.0); // dont multiply with view!
}
