#version 130

uniform vec4 speed;

out vec4 fragColor;

void main()
{
	fragColor = vec4(length(speed) / 10);
}
