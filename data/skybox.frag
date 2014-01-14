#version 130

uniform samplerCube texCube;

in vec3 v_tex;
//layout (location = 0) 
out vec4 fragColor;

void main() {
	fragColor = texture(texCube, v_tex);
}
