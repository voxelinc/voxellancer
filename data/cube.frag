#version 400

// uniform sampler2D texture;

in vec2 v_uv;
in vec3 normal;

layout (location = 0) out vec4 fragColor;

void main()
{
    vec3 n_normal = normalize(normal);
    float diffuse = dot(n_normal, normalize(vec3(0.1f, 0.2f, 1.0f)));
	//fragColor = vec4(n_normal + 1.0f / 2.0f, 1.0f);
    fragColor = vec4(vec3(diffuse), 1.0);
}
