#version 130

uniform sampler2D texture;
uniform vec2 offset;
uniform vec2 scale;

in vec2 v_screenCoord;

out vec2 f_texCoord;


void main() {
    vec2 coord = v_screenCoord * scale + offset;

    gl_Position = vec4(coord, 0, 1);
    f_texCoord = v_screenCoord + 1.0 / 2.0;
}

