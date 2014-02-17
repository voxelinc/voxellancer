#version 330

layout(location=0) in vec3 v_vertex;

out vec2 v_uv;

void main(void) {
    v_uv = v_vertex.xy * 0.5 + 0.5;
    gl_Position = vec4(v_vertex, 1.0);
}
