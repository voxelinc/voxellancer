#version 330

in vec3 a_vertex;
out vec2 v_tex;

void main() {
    v_tex = -a_vertex.xy * 0.5 + 0.5;

    gl_Position = vec4(a_vertex, 1.0);
}
