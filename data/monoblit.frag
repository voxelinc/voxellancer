#version 130

uniform sampler2D texture;

in vec2 f_texCoord;

out vec3 fragColor;


void main() {
    fragColor = texture2D(texture, f_texCoord);
}

