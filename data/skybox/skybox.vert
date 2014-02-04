#version 330

uniform mat4 viewProjectionInverted;

in vec3 a_vertex;
out vec3 v_tex;

void main() {
    v_tex = (viewProjectionInverted * vec4(a_vertex, 1.0)).xyz;
    v_tex.x = -v_tex.x; // we want to see the cube from the inside

    // no model, no projection - our coordinates are device coordinates already
    gl_Position = vec4(a_vertex, 1.0);
}
