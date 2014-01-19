#version 130

uniform vec2 offset;
uniform vec2 scale;
uniform sampler2D texture;

in vec2 v_vertex;

out vec2 f_viewportC;


void main() {
    vec2 screenC = (v_vertex + 1.0f) / 2.0 * scale + offset;

    vec2 coord = (screenC * 2) - 1;

    gl_Position = vec4(coord, 0, 1);

    f_viewportC = v_vertex;
}

