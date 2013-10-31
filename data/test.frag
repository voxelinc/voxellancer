#version 330

uniform samplerCube texture;

in vec3 v_tex;
layout (location = 0) out vec4 fragColor;

void main()
{
	fragColor = texture(texture, v_tex);
}
