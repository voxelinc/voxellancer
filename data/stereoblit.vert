#version 130

uniform vec2 offset;
uniform vec2 scale;
uniform sampler2D texture;

in vec2 v_vertex;

out vec2 f_texCoord;


void main() {
    vec2 normalizedCoords = (v_vertex + 1.0f) / 2.0 * scale + offset;

    vec2 coord = (normalizedCoords * 2) - 1;

    gl_Position = vec4(coord, 0, 1);
    f_texCoord = (v_vertex + vec2(1.0, 1.0)) / 2.0;
}

