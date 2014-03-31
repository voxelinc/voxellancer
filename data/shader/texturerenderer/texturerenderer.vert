#version 330

in vec3 a_vertex;
out vec2 v_tex;

void main() {
    v_tex = vec2(a_vertex.x * 0.5 + 0.5, -a_vertex.y * 0.5 + 0.5);

    gl_Position = vec4(a_vertex, 1.0);
}
