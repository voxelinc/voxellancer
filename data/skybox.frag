#version 330

uniform samplerCube texCube;

in vec3 v_tex;

layout(location=0) out vec4 fragColor;
layout(location=1) out vec4 normalz;
layout(location=2) out vec4 emissiveness;

void main() {
	fragColor = texture(texCube, v_tex);
    emissiveness = vec4(vec3(0.05),1.0);
    normalz = vec4(0);
}
