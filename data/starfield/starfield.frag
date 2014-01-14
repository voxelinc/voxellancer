#version 150

uniform vec4 speed;

in vec2 f_uv;
in float f_brightness;

out vec4 fragColor;

void main()
{
    float d = length(vec2(0.5) - f_uv)*2;

	fragColor = vec4(vec3(1.0), (0.9-d)*f_brightness);
    //fragColor = vec4(1.0);
}
