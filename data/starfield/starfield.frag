#version 130

uniform vec4 speed;

in vec2 v_uv;
in float v_brightness;

out vec4 fragColor;

void main()
{
    float d = length(vec2(0.5) - v_uv)*2;

	fragColor = vec4(vec3(1.0), (0.9-d)*v_brightness);
}
