#version 130

uniform sampler2D texture;

in vec2 f_texCoord;

out vec4 fragColor;


void main() {
    fragColor = texture2D(texture, f_texCoord);
}

