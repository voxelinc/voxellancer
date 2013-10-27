#version 330

// uniform sampler2D texture;

in vec2 v_uv;
in vec3 normal;
in vec4 position;

layout (location = 0) out vec4 fragColor;

void main()
{
    float diffuse = dot(normal, normalize(vec3(0.3f, 0.2f, 9.0f)));
	//fragColor = vec4(normal + 1.0f / 2.0f, 1.0f);
    fragColor = vec4(vec3(diffuse), 1.0);
}
